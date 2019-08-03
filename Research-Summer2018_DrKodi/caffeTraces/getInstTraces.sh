#KodiLab-summer2018

#Script to run pintool described at https://github.com/stevenpelley/atomic-memory-trace
#on several caffe examples and move output files

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
~/pin-linux-3.6/pin -t ~/pin-linux-3.6/source/tools/SimpleExamples/obj-intel64/trace.so -o lenetMnistInstructionTrace.out -- ~/caffe/examples/mnist/train_lenet.sh

#CIFAR10 - Cifar10 quick solver
~/pin-linux-3.6/pin -t ~/pin-linux-3.6/source/tools/SimpleExamples/obj-intel64/trace.so -o cifar10InstTrace.out -- ~/caffe/examples/cifar10/train_quick.sh

#MNIST - Siamese solver
~/pin-linux-3.6/pin -t ~/pin-linux-3.6/source/tools/SimpleExamples/obj-intel64/trace.so -o siameseInstructionTrace.out -- ~/caffe/examples/siamese/train_mnist_siamese.sh


#Move PIN output to Output_Files/ directory
mv *.out ~/KodiLab-summer2018/caffeTraces/full_instruction_traces
