# Get started with nifti: Read
I needed to learn the basics of reading nifti images in C/C++. I read some examples here and there. Some were too simple/not informative enough and others were too long/with too much detail. So I decided to write my own to quickly remind myself about how it is done. Maybe you will find it useful also.

Here are some features of the short code:

- The intention is to demonstrate how to read three dimensional structure images. Hopefully after getting started with this, reading fMRI and other higher dimensional images would be easier.
- It supports compressed (.nii.gz) and the uncompressed (.nii) files.
- Several commonly used datatypes are supported.
- There is some focus on explaining qform and sform as well as swtiching between pixel/real spaces.
- The executable will display some information fetched from the nifti header and also will write the value of a pixel at a given position -> this is to demonstrate how to read the image data itself.

## Installation
I wrote this on a Linux machine. I compile it just with:

> make


Usage example: ./readNifti test.nii.gz 58 30 57

The above command will print out some information about the test image and write the value of the pixel at i=58, j=30, k=57.


## Notes
Here are some key points that might be useful to keep in mind:

- The compilation should not require any other dependencies than zlib which is needed to read compressed files. All the necessary files for nifti are trimmed under the nifticlib-2.0.0 folder which can be downloaded from https://sourceforge.net/projects/niftilib/files/nifticlib/.
- Check the Makefile to understand how the compilation is done. Importantly do not forget the "-D HAVE_ZLIB" flag to enable compressed file support.
- To enable support for a variety of datatypes, I used an "abstract class" and a "pure virtual function". You might want to have a look at these key words if more details are required.
