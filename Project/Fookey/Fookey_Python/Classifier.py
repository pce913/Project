# Run shell by command "python test.py /FOOD /TEST/img.jpg" 
# -> Second Argument is MainCategoty Folder
# -> Third Argument is Test image path
import sys
import os
import numpy as np
import scipy.io
from scipy.misc import imread, imresize
import matplotlib.pyplot as plt
import tensorflow as tf
import VGG as vgg

cwd = os.getcwd()
category_path = cwd + sys.argv[1]

imgsize = [64, 64]      # The reshape size
use_gray = 0            # Grayscale
data_name = "data4vgg"  # Save name
valid_exts = [".jpg",".gif",".png",".tga", ".jpeg"]

categories = sorted(os.listdir(category_path))
nclass = len(categories)

IMG_PATH = cwd + sys.argv[2]
testimage = imread(IMG_PATH)

if use_gray:
    grayimg  = rgb2gray(testimage)    
    testimg   = np.ndarray((1, imgsize[0]*imgsize[1])) 
else:
    grayimg  = testimage
    testimg   = np.ndarray((1, imgsize[0]*imgsize[1]*3))


testimagesmall = imresize(grayimg, [imgsize[0], imgsize[1]])/255.
testimg[0, :] =  np.reshape(testimagesmall, (1, -1))
dim = testimg.shape[1]

tensor = np.ndarray((1, imgsize[0], imgsize[1], 3))
currimg = testimg[0, :]
currimg = np.reshape(currimg, [imgsize[0], imgsize[1], 3])
tensor[0, :, :, :] = currimg

VGG_PATH = cwd + "/data/mainCategory-vgg-verydeep-19.mat"
with tf.Graph().as_default(), tf.Session() as sess:
    with tf.device("/gpu:0"):
        img_placeholder = tf.placeholder(tf.float32
                                         , shape=(None, imgsize[0], imgsize[1], 3))
        nets, mean_pixel = vgg.net(VGG_PATH, img_placeholder)
        # one picture
        features = nets['relu5_4'].eval(feed_dict={img_placeholder: tensor})
        
vectorized  = np.ndarray((1, 4*4*512))
curr_feat = features[0, :, :, :]
curr_feat_vec = np.reshape(curr_feat, (1, -1))
vectorized[0, :] = curr_feat_vec


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
with tf.device("/gpu:0"):
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
    init = tf.global_variables_initializer()


# Launch the graph
sess = tf.Session()
sess.run(init)

# one picture
pred = sess.run(_pred, feed_dict={x: vectorized, keepratio:1.})

y_idx = np.argmax(pred)
score = pred[0][y_idx]
category_name = categories[y_idx]

print("category: %s" % category_name) 
        
#subCategory-dish-vgg-verydeep-19.mat
#subCategory-noodle-vgg-verydeep-19.mat
#subCategory-rice-vgg-verydeep-19.mat
#subCategory-side-vgg-verydeep-19.mat
#subCategory-soup-vgg-verydeep-19.mat

print category_name
category_path = cwd + "/SUB/" + category_name
categories = sorted(os.listdir(category_path))
nclass = len(categories)

# Get conv features
VGG_PATH = cwd + "/data/subCategory-" + category_name + "-vgg-verydeep-19.mat"
with tf.Graph().as_default(), tf.Session() as sess:
    with tf.device("/gpu:0"):
        img_placeholder = tf.placeholder(tf.float32
                                         , shape=(None, imgsize[0], imgsize[1], 3))
        nets, mean_pixel = vgg.net(VGG_PATH, img_placeholder)
        
        features = nets['relu5_4'].eval(feed_dict={img_placeholder: tensor})


vectorized  = np.ndarray((1, 4*4*512))
curr_feat = features[0, :, :, :]
curr_feat_vec = np.reshape(curr_feat, (1, -1))
vectorized[0, :] = curr_feat_vec

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
with tf.device("/gpu:0"):
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
    init = tf.global_variables_initializer()
    
# Launch the graph
sess = tf.Session()
sess.run(init)

pred = sess.run(_pred, feed_dict={x: vectorized, keepratio:1.})

y_idx = np.argmax(pred)
score = pred[0][y_idx]
category_name = categories[y_idx]

print("category: %s " % category_name)