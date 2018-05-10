
# coding: utf-8

# In[4]:

# Import packs
import numpy as np
import os
import scipy.io
from scipy.misc import imread, imresize
import matplotlib.pyplot as plt
#import skimage.io
#import skimage.transform
import tensorflow as tf
get_ipython().magic(u'matplotlib inline')
cwd = os.getcwd()

# Configure the locations of the images and reshaping sizes
# ------------------------------------------------------------------- #
#paths = {"images/cats", "images/dogs"}
#paths = {"images/car_dataset/sedan", "images/car_dataset/suv", "images/car_dataset/sedan", "images/car_dataset/truck"}
#paths = {"images/painting_dataset/pencil", "images/painting_dataset/pastel", "images/painting_dataset/etc"}
#paths = {"images/painting_dataset/pencil", "images/painting_dataset/pastel"}
cate_path = cwd + "/images5"
#cate_path = cwd + "/images/car_dataset"
#cate_path = cwd + "/images/painting_dataset"
imgsize = [64, 64]      # The reshape size
use_gray = 0            # Grayscale
data_name = "data4vgg"  # Save name
valid_exts = [".jpg",".gif",".png",".tga", ".jpeg"]
# ------------------------------------------------------------------- #

imgcnt = 0
categories = sorted(os.listdir(cate_path))
nclass = len(categories)

for category in categories:
    for f in os.listdir(cate_path + "/" + category):
        fullpath = cwd + "/" + category
        if os.path.splitext(f)[1].lower() not in valid_exts:
            continue
        fullpath = os.path.join(fullpath, f)
        imgcnt = imgcnt + 1
        
# Grayscale
def rgb2gray(rgb):
    if len(rgb.shape) is 3:
        return np.dot(rgb[...,:3], [0.299, 0.587, 0.114])
    else:
        return rgb
    
if use_gray:
    totalimg   = np.ndarray((imgcnt, imgsize[0]*imgsize[1]))
else:
    totalimg   = np.ndarray((imgcnt, imgsize[0]*imgsize[1]*3))
totallabel = np.ndarray((imgcnt, nclass))
imgcnt     = 0
ignored_cnt = 0
for i, relpath in zip(range(nclass), categories):
    path = cate_path + "/" + relpath
    flist = os.listdir(path)
    for f in flist:
        if os.path.splitext(f)[1].lower() not in valid_exts:
            continue
        fullpath = os.path.join(path, f)
        currimg  = imread(fullpath)

        #print(f)
        # Convert to grayscale  
        if use_gray:
            grayimg  = rgb2gray(currimg)
            #print(currimg.shape)
        else:
            grayimg  = currimg
            #print(currimg.shape)
        
        # (희경)에러가 나서 continue
        if (len(currimg.shape)==2 or currimg.shape[2]!=3):    
            #print("%s ignored" % f)
            ignored_cnt = ignored_cnt + 1
            continue 
                            
        # Reshape
        graysmall = imresize(grayimg, [imgsize[0], imgsize[1]])/255.
        grayvec   = np.reshape(graysmall, (1, -1))
        
        #print(grayvec.shape)
        #print(totalimg[imgcnt, :].shape)
        # Save 
        totalimg[imgcnt, :] = grayvec
        totallabel[imgcnt, :] = np.eye(nclass, nclass)[i]
        imgcnt    = imgcnt + 1
        
# Divide total data into training and test set
randidx    = np.random.randint(imgcnt, size=imgcnt)
trainidx   = randidx[0:int(4*imgcnt/5)]
testidx    = randidx[int(4*imgcnt/5):imgcnt]
trainimg   = totalimg[trainidx, :]
trainlabel = totallabel[trainidx, :]
testimg    = totalimg[testidx, :]
testlabel  = totallabel[testidx, :]
ntrain     = trainimg.shape[0]
nclass     = trainlabel.shape[1]
dim        = trainimg.shape[1]
ntest      = testimg.shape[0]

    
def net(data_path, input_image):
    layers = (
        'conv1_1', 'relu1_1', 'conv1_2', 'relu1_2', 'pool1',
        'conv2_1', 'relu2_1', 'conv2_2', 'relu2_2', 'pool2',
        'conv3_1', 'relu3_1', 'conv3_2', 'relu3_2', 'conv3_3',
        'relu3_3', 'conv3_4', 'relu3_4', 'pool3',
        'conv4_1', 'relu4_1', 'conv4_2', 'relu4_2', 'conv4_3',
        'relu4_3', 'conv4_4', 'relu4_4', 'pool4',
        'conv5_1', 'relu5_1', 'conv5_2', 'relu5_2', 'conv5_3',
        'relu5_3', 'conv5_4', 'relu5_4'
    )
    data = scipy.io.loadmat(data_path)
    mean = data['normalization'][0][0][0]
    mean_pixel = np.mean(mean, axis=(0, 1))
    weights = data['layers'][0]
    net = {}
    current = input_image
    for i, name in enumerate(layers):
        kind = name[:4]
        if kind == 'conv':
            kernels, bias = weights[i][0][0][0][0]
            # matconvnet: weights are [width, height, in_channels, out_channels]
            # tensorflow: weights are [height, width, in_channels, out_channels]
            kernels = np.transpose(kernels, (1, 0, 2, 3))
            bias = bias.reshape(-1)
            current = _conv_layer(current, kernels, bias)
        elif kind == 'relu':
            current = tf.nn.relu(current)
        elif kind == 'pool':
            current = _pool_layer(current)
        net[name] = current
    assert len(net) == len(layers)
    return net, mean_pixel
def _conv_layer(input, weights, bias):
    conv = tf.nn.conv2d(input, tf.constant(weights), strides=(1, 1, 1, 1),
            padding='SAME')
    return tf.nn.bias_add(conv, bias)
def _pool_layer(input):
    return tf.nn.max_pool(input, ksize=(1, 2, 2, 1), strides=(1, 2, 2, 1),
            padding='SAME')
def preprocess(image, mean_pixel):
    return image - mean_pixel
def unprocess(image, mean_pixel):
    return image + mean_pixel


# 그림 한 장
cat_IMG_PATH = cwd + "/test/testimage8.jpg"
#cat_IMG_PATH = cwd + "/images/sport3.jpg"
#cat_IMG_PATH = cwd + "/images/Degas.png"
cat_image = imread(cat_IMG_PATH)
cat_tensor = np.ndarray((1, imgsize[0], imgsize[1], 3))
# 줄이기
cat_image_small = imresize(cat_image, [imgsize[0], imgsize[1]])/255.  # [64, 64, 3]
#currimg = np.reshape(currimg, (1, -1))   # 일렬로 피기
cat_tensor[0, :, :, :] = cat_image_small

# Get conv features
VGG_PATH = cwd + "/data/imagenet-vgg-verydeep-19.mat"
with tf.Graph().as_default(), tf.Session() as sess:
    with tf.device("/cpu:0"):
        img_placeholder = tf.placeholder(tf.float32
                                         , shape=(None, imgsize[0], imgsize[1], 3))
        nets, mean_pixel = net(VGG_PATH, img_placeholder)
        # 그림 한 장
        cat_features = nets['relu5_4'].eval(feed_dict={img_placeholder: cat_tensor})

cat_vectorized  = np.ndarray((1, 4*4*512))
curr_feat = cat_features[0, :, :, :]
curr_feat_vec = np.reshape(curr_feat, (1, -1))
cat_vectorized[0, :] = curr_feat_vec

# Parameters
learning_rate   = 0.0001
training_epochs = 100
batch_size      = 100
display_step    = 10
# tf Graph input
x = tf.placeholder(tf.float32, [None, 4*4*512])
y = tf.placeholder(tf.float32, [None, nclass])
keepratio = tf.placeholder(tf.float32)
# Network
with tf.device("/cpu:0"):
    n_input  = dim
    n_output = nclass
    weights  = {
        'wd1': tf.Variable(tf.random_normal([4*4*512, 1024], stddev=0.1)),
        'wd2': tf.Variable(tf.random_normal([1024, n_output], stddev=0.1))
    }
    biases   = {
        'bd1': tf.Variable(tf.random_normal([1024], stddev=0.1)),
        'bd2': tf.Variable(tf.random_normal([n_output], stddev=0.1))
    }
    def conv_basic(_input, _w, _b, _keepratio):
        # Input
        _input_r = _input
        # Vectorize
        _dense1 = tf.reshape(_input_r, [-1, _w['wd1'].get_shape().as_list()[0]])
        # Fc1
        _fc1 = tf.nn.relu(tf.add(tf.matmul(_dense1, _w['wd1']), _b['bd1']))
        _fc_dr1 = tf.nn.dropout(_fc1, _keepratio)
        # Fc2
        _out = tf.add(tf.matmul(_fc_dr1, _w['wd2']), _b['bd2'])
        # Return everything
        out = {'input_r': _input_r, 'dense1': _dense1,
            'fc1': _fc1, 'fc_dr1': _fc_dr1, 'out': _out }
        return out
    # Functions! 
    _pred = conv_basic(x, weights, biases, keepratio)['out']
    cost = tf.reduce_mean(tf.nn.softmax_cross_entropy_with_logits(logits =  _pred, labels = y))
    optm = tf.train.AdamOptimizer(learning_rate=learning_rate).minimize(cost)
    _corr = tf.equal(tf.argmax(_pred,1), tf.argmax(y,1)) 
    accr = tf.reduce_mean(tf.cast(_corr, tf.float32)) 
    init = tf.initialize_all_variables()

# Launch the graph
sess = tf.Session()
sess.run(init)

# 그림 한 장
cat_pred = sess.run(_pred, feed_dict={x: cat_vectorized, keepratio:1.})

y_idx = np.argmax(cat_pred)
score = cat_pred[0][y_idx]
cate_name = categories[y_idx],
print(cat_pred)
print("category: %s" % cate_name)

