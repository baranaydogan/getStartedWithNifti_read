#include <iostream>
#include <iomanip>
#include <nifti1_io.h>

// All the information below is obtained from nifti1.h

class NiftiDataAccessor{
public:
	virtual float get(void *_data, int index) = 0;
	virtual ~NiftiDataAccessor() = 0;
};
NiftiDataAccessor::~NiftiDataAccessor() { }

template<class T> class NiftiDataAccessor_ForType : public NiftiDataAccessor {
public:
	virtual float get(void *_data, int index) {
		return ((T*) _data)[index];
	}

};

int main(int argc, char * argv[]) {

	if (argc!=5) {
		std::cout << std::endl << "This example is mainly intended to demonstrate how to read 3 dimensional structural images and access data" << std::endl << std::endl;
		std::cout << "USAGE EXAMPLE: ./readNifti test.nii.gz 58 30 57 " << std::endl;
		std::cout << "will print out some information about the test image and write the value of the pixel at i=58, j=30, k=57" << std::endl << std::endl;
		return 1;
	}


	std::cout << std::setprecision(3) << std::fixed; // This just writes all floats with fixed 3 digits after the comma, so the matrices appears nicer

	nifti_image * nim = NULL;

	nim = nifti_image_read(argv[1],1);

	// nifti_image_infodump(nim);


	std::cout << std::endl;
	std::cout << "Data description:       " << nim->descrip << std::endl;
	std::cout << "Nifti type:             ";
	switch (nim->nifti_type) {
	case 0:    std::cout<<"Analyze"                          << std::endl; break;
	case 1:    std::cout<<"NIFTI-1 (1 file)"                 << std::endl; break;
	case 2:    std::cout<<"NIFTI-2 (2 file)"                 << std::endl; break;
	case 3:    std::cout<<"NIFTI-ASCII (1 file)"             << std::endl; break;
	default:   std::cout<<"Not applicable"                   << std::endl; break;
	}
	std::cout << std::endl;

	std::cout << "Number of dimensions:   "   << nim->dim[0] << std::endl;
	std::cout << "Dimensions:             ["  << nim->dim[1] << " x " << nim->dim[2] << " x " << nim->dim[3] << "]" << std::endl;
	std::cout << "Number of voxels:       "   << nim->nvox << std::endl;
	std::cout << "Number of bytes/voxel:  "   << nim->nbyper << std::endl;

	std::cout << "Pixdim:                 [" << nim->pixdim[1] << " x " << nim->pixdim[2] << " x " << nim->pixdim[3] << "]" << std::endl;

	std::cout << "Unit of pixdim:         ";
	switch (nim->xyz_units) {
	case 0:    std::cout<<"unknown"                          << std::endl; break;
	case 1:    std::cout<<"meter"                            << std::endl; break;
	case 2:    std::cout<<"mm"                               << std::endl; break;
	case 3:    std::cout<<"micron"                           << std::endl; break;
	default:   std::cout<<"Not applicable"                   << std::endl; break;
	}

	// qform and sform are used to determine the orientation and location in space
	//
	// qform -> It is used to relate the scanned subject's physical space to the scanner's physical space.
	//          For example, if you are imaging the same subject on different days, qform can be used to align the images on the scanner space.
	//          That is why it is a rigid transform, i.e.: includes only translations and rotations.
	std::cout << std::endl;
	std::cout << "qform:                  " << nim->qform_code << " -> ";
	switch (nim->qform_code) {
	case 0:    std::cout<<"a scanner based anatomical coordinate is NOT specified"           << std::endl; break;
	case 1:    std::cout<<"a scanner based anatomical coordinate is specified"               << std::endl; break;
	default:   std::cout<<"Not applicable"                   << std::endl; break;
	}

	// nifti uses:
	// x,y,z are for the continuous,              i.e.: physical or real coordinates.
	// i,j,k are for the voxel index coordinates, i.e.: pixel space.
	// x,y,z refer to the CENTER of voxels in RAS orientation (+x = Right  +y = Anterior  +z = Superior)
	//
	std::cout << "qto_xyz:                [x y z 1]' = qto_xyz * [i j k 1]' and qto_xyz is:" << std::endl;
	std::cout << "                          " << nim->qto_xyz.m[0][0] << " " << nim->qto_xyz.m[0][1]  << " " << nim->qto_xyz.m[0][2]  << " " << nim->qto_xyz.m[0][3] << std::endl;
	std::cout << "                          " << nim->qto_xyz.m[1][0] << " " << nim->qto_xyz.m[1][1]  << " " << nim->qto_xyz.m[1][2]  << " " << nim->qto_xyz.m[1][3] << std::endl;
	std::cout << "                          " << nim->qto_xyz.m[2][0] << " " << nim->qto_xyz.m[2][1]  << " " << nim->qto_xyz.m[2][2]  << " " << nim->qto_xyz.m[2][3] << std::endl;
	std::cout << "                          " << nim->qto_xyz.m[3][0] << " " << nim->qto_xyz.m[3][1]  << " " << nim->qto_xyz.m[3][2]  << " " << nim->qto_xyz.m[3][3] << std::endl;

	std::cout << "qto_ijk:                [i j k 1]' = qto_ijk * [x y z 1]' and qto_ijk is:" << std::endl;
	std::cout << "                          " << nim->qto_ijk.m[0][0] << " " << nim->qto_ijk.m[0][1]  << " " << nim->qto_ijk.m[0][2]  << " " << nim->qto_ijk.m[0][3] << std::endl;
	std::cout << "                          " << nim->qto_ijk.m[1][0] << " " << nim->qto_ijk.m[1][1]  << " " << nim->qto_ijk.m[1][2]  << " " << nim->qto_ijk.m[1][3] << std::endl;
	std::cout << "                          " << nim->qto_ijk.m[2][0] << " " << nim->qto_ijk.m[2][1]  << " " << nim->qto_ijk.m[2][2]  << " " << nim->qto_ijk.m[2][3] << std::endl;
	std::cout << "                          " << nim->qto_ijk.m[3][0] << " " << nim->qto_ijk.m[3][1]  << " " << nim->qto_ijk.m[3][2]  << " " << nim->qto_ijk.m[3][3] << std::endl;
	std::cout << std::endl;

	// qto_xyz and qto_ijk are a part of the nifti1.io.h for convenience but not included in the nifti header.
	// The nifti header uses the following parameters that are converted to qto_xyz and qto_ijk by the nifti1.io.h: qoffset_x, qoffset_y, qoffset_z, quatern_b, quatern_c, quatern_d, qfac
	// Therefore if you for example translate an image and need to change the header information for a consistent qform, these parameters need to be changed before writing.
	// You can use the convenience function "nifti_mat44_to_quatern" to do this, which is a part of the nifti1.io.h. Shortly the parameters can be explained as follows:
	//          - The offset parameters are just shifts in the physical space.
	//          - quatern_b, quatern_c, quatern_d are used to represent a rotation matrix using quaternions.
	//          - The rotation matrix is computed in two different ways, which is indicated by the qfac parameter.
	//          - qfac is stored in pixdim[0]. It must be either -1 or 1. (When reading, if for some reason pixdim[0]=0 then qfac=1 should be assumed.)


	// sform -> It is used to relate the scanner's physical space to a standard space.
	std::cout << "sform:                  "  << nim->sform_code << " -> ";
	switch (nim->sform_code) {
	case 0:    std::cout<<"a transformation mapping to a standard space is NOT defined"                                                                     << std::endl; break;
	case 1:    std::cout<<"a transformation mapping the scanner space to a scanner based anatomical space is defined"                                       << std::endl; break;
	case 2:    std::cout<<"a transformation mapping the scanner space to another file's anatomical space (can for example be anatomical truth) is defined"  << std::endl; break;
	case 3:    std::cout<<"a transformation mapping the scanner space to Talairach-Tournoux Atlas is defined"                                               << std::endl; break;
	case 4:    std::cout<<"a transformation mapping the scanner space to MNI 152 normalized coordinates is defined"                                         << std::endl; break;
	default:   std::cout<<"Not applicable"                   << std::endl; break;
	}

	std::cout << "sto_xyz:                [x y z 1]' = sto_xyz * [i j k 1]' and sto_xyz is:" << std::endl;
	std::cout << "                          " << nim->sto_xyz.m[0][0] << " " << nim->sto_xyz.m[0][1]  << " " << nim->sto_xyz.m[0][2]  << " " << nim->sto_xyz.m[0][3] << std::endl;
	std::cout << "                          " << nim->sto_xyz.m[1][0] << " " << nim->sto_xyz.m[1][1]  << " " << nim->sto_xyz.m[1][2]  << " " << nim->sto_xyz.m[1][3] << std::endl;
	std::cout << "                          " << nim->sto_xyz.m[2][0] << " " << nim->sto_xyz.m[2][1]  << " " << nim->sto_xyz.m[2][2]  << " " << nim->sto_xyz.m[2][3] << std::endl;
	std::cout << "                          " << nim->sto_xyz.m[3][0] << " " << nim->sto_xyz.m[3][1]  << " " << nim->sto_xyz.m[3][2]  << " " << nim->sto_xyz.m[3][3] << std::endl;

	std::cout << "sto_ijk:                [i j k 1]' = sto_ijk * [x y z 1]' and sto_ijk is:" << std::endl;
	std::cout << "                          " << nim->sto_ijk.m[0][0] << " " << nim->sto_ijk.m[0][1]  << " " << nim->sto_ijk.m[0][2]  << " " << nim->sto_ijk.m[0][3] << std::endl;
	std::cout << "                          " << nim->sto_ijk.m[1][0] << " " << nim->sto_ijk.m[1][1]  << " " << nim->sto_ijk.m[1][2]  << " " << nim->sto_ijk.m[1][3] << std::endl;
	std::cout << "                          " << nim->sto_ijk.m[2][0] << " " << nim->sto_ijk.m[2][1]  << " " << nim->sto_ijk.m[2][2]  << " " << nim->sto_ijk.m[2][3] << std::endl;
	std::cout << "                          " << nim->sto_ijk.m[3][0] << " " << nim->sto_ijk.m[3][1]  << " " << nim->sto_ijk.m[3][2]  << " " << nim->sto_ijk.m[3][3] << std::endl;
	std::cout << std::endl;

	// sto_xyz and sto_ijk are a part of the nifti1.io.h for convenience but not included in the nifti header.
	// The nifti header uses the following parameters that are converted to sto_xyz and sto_ijk by the nifti1.io.h: srow_x[4], srow_y[4], srow_z[4].
	// Where srow_x[4], srow_y[4] and srow_z[4] are the first, second and third rows of sto_xyz.m respectively.

	NiftiDataAccessor *accessor = NULL;
	std::cout << "Datatype:               " ;
	switch (nim->datatype) {
	case 0:    std::cout<<"unknown"                          << std::endl; std::cout << "I don't know what to do with this data type" << std::endl; return 1; break;
	case 1:    std::cout<<"bool, binary"                     << std::endl; std::cout << "I don't know what to do with this data type" << std::endl; return 1; break;
	case 2:    std::cout<<"uint8, unsigned char"             << std::endl; accessor = new NiftiDataAccessor_ForType<unsigned char>; break;
	case 4:    std::cout<<"int16, signed short"              << std::endl; accessor = new NiftiDataAccessor_ForType<short>; break;
	case 8:    std::cout<<"int32, signed int"                << std::endl; accessor = new NiftiDataAccessor_ForType<int>; break;
	case 16:   std::cout<<"float32"                          << std::endl; accessor = new NiftiDataAccessor_ForType<float>; break;
	case 32:   std::cout<<"complex64"                        << std::endl; std::cout << "I don't know what to do with this data type" << std::endl; return 1; break;
	case 64:   std::cout<<"float64, double"                  << std::endl; accessor = new NiftiDataAccessor_ForType<double>; break;
	case 128:  std::cout<<"rgb24"                            << std::endl; std::cout << "I don't know what to do with this data type" << std::endl; return 1; break;
	case 255:  std::cout<<"all?"                             << std::endl; std::cout << "I don't know what to do with this data type" << std::endl; return 1; break;
	case 256:  std::cout<<"int8, signed char"                << std::endl; accessor = new NiftiDataAccessor_ForType<signed char>; break;
	case 512:  std::cout<<"uint16, unsigned short"           << std::endl; accessor = new NiftiDataAccessor_ForType<unsigned short>; break;
	case 768:  std::cout<<"uint32, unsigned int"             << std::endl; accessor = new NiftiDataAccessor_ForType<unsigned int>; break;
	case 1024: std::cout<<"int64, long long int"             << std::endl; accessor = new NiftiDataAccessor_ForType<long long int>; break;
	case 1280: std::cout<<"uint64, unsigned long long int"   << std::endl; accessor = new NiftiDataAccessor_ForType<unsigned long long int>; break;
	case 1536: std::cout<<"float128, long double"            << std::endl; accessor = new NiftiDataAccessor_ForType<long double>; break;
	case 1792: std::cout<<"complex128"                       << std::endl; std::cout << "I don't know what to do with this data type" << std::endl; return 1; break;
	case 2048: std::cout<<"complex256"                       << std::endl; std::cout << "I don't know what to do with this data type" << std::endl; return 1; break;
	case 2304: std::cout<<"rgba32"                           << std::endl; std::cout << "I don't know what to do with this data type" << std::endl; return 1; break;
	default:   std::cout<<"Not applicable"                   << std::endl; std::cout << "I don't know what to do with this data type" << std::endl; return 1; break;
	}

	int i = atoi(argv[2]);
	int j = atoi(argv[3]);
	int k = atoi(argv[4]);

	float x = nim->sto_xyz.m[0][0]*i + nim->sto_xyz.m[0][1]*j + nim->sto_xyz.m[0][2]*k + nim->sto_xyz.m[0][3];
	float y = nim->sto_xyz.m[1][0]*i + nim->sto_xyz.m[1][1]*j + nim->sto_xyz.m[1][2]*k + nim->sto_xyz.m[1][3];
	float z = nim->sto_xyz.m[2][0]*i + nim->sto_xyz.m[2][1]*j + nim->sto_xyz.m[2][2]*k + nim->sto_xyz.m[2][3];

	std::cout << "Pixel coordinates       = [" << i << " , " << j << " , " << k << "] -> Physical coordinates = [" << x << " , " << y << " , " << z << "]" << std::endl;

	i = nim->sto_ijk.m[0][0]*x + nim->sto_ijk.m[0][1]*y + nim->sto_ijk.m[0][2]*z + nim->sto_ijk.m[0][3];
	j = nim->sto_ijk.m[1][0]*x + nim->sto_ijk.m[1][1]*y + nim->sto_ijk.m[1][2]*z + nim->sto_ijk.m[1][3];
	k = nim->sto_ijk.m[2][0]*x + nim->sto_ijk.m[2][1]*y + nim->sto_ijk.m[2][2]*z + nim->sto_ijk.m[2][3];

	std::cout << "Physical coordinates    = [" << x << " , " << y << " , " << z << "] -> Pixel coordinates    = [" << i << " , " << j << " , " << k << "]" << std::endl;



	int index 	= i + j*nim->dim[1] + k*nim->dim[1]*nim->dim[2];

	std::cout << "Value at [" << i << "," << j << "," << k <<"]     = " << accessor->get(nim->data,index) <<  std::endl;

	nifti_image_free( nim );

	return 0;


}
