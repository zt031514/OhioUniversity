#KodiLab-summer2018

#Script to run pintool pinatrace

#Get data
cd ~/caffe
./data/mnist/get_mnist.sh
./data/cifar10/get_cifar10.sh

#Prepare data/create lmdb
./examples/mnist/create_mnist.sh
./examples/cifar10/create_cifar10.sh
./examples/siamese/create_mnist_siamese.sh

#Run pintool on caffe using LeNet, CIFAR10 solver, and siamese applications

#MNIST - LeNet solver
~/pin-linux-3.6/pin -t ~/pin-linux-3.6/source/tools/ManualExamples/obj-intel64/pinatrace.so -- ~/caffe/examples/mnist/train_lenet.sh

mv pinatrace.out ~/KodiLab-summer2018/caffeTraces/mem_access_traces/lenetMemTrace.out

#CIFAR10 - Cifar10 quick solver
~/pin-linux-3.6/pin -t ~/pin-linux-3.6/source/tools/ManualExamples/obj-intel64/pinatrace.so -- ~/caffe/examples/cifar10/train_quick.sh

mv pinatrace.out ~/KodiLab-summer2018/caffeTraces/mem_access_traces/cifar10MemTrace.out

#MNIST - Siamese solver
~/pin-linux-3.6/pin -t ~/pin-linux-3.6/source/tools/ManualExamples/obj-intel64/pinatrace.so -- ~/caffe/examples/siamese/train_mnist_siamese.sh

mv pinatrace.out ~/KodiLab-summer2018/caffeTraces/mem_access_traces/siameseMemTrace.out
