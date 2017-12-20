# Get started with nifti: Read

I needed to learn the basics of reading nifti images in C/C++. I read some examples here and there. Some were too simple/not informative enough and others were too long/with too much detail. So I decided to write my own to quickly remind myself about how it is done. Maybe you will find it useful also.

Here are some features of the short code:

- The intention is intended to demonstrate how to read three dimensional structure images. Hopefully after getting started with this, reading fMRI and other higher dimensional images would be easier.
- It supports compressed (.nii.gz) and the uncompressed (.nii) files.
- Several commonly used datatypes are supported.
- The executable will display some information fetched from the nifti header and also write the value of the pixel at the specified position -> this is to demonstrate how to read the image data basically.

Usage example: ./readNifti test.nii.gz 58 30 57 
This will print out some information about the test image and write the value of the pixel at i=58, j=30, k=57


Here are some key points that might be useful to keep in mind:

- The compilation should not require any other dependencies other than zlib which is needed to read compressed files. All the necessary files for nifti are trimmed under nifticlib-2.0.0 which can be downloaded from https://sourceforge.net/projects/niftilib/files/nifticlib/.
- Check the Makefile to understand how to compilation is done. Importantly do not forget the "-D HAVE_ZLIB" flag to enable compressed file support.
- To enable support for a variety of datatypes, I used abstract classes and a pure virtual function. You might want to have a look at these key words if more details are required.
