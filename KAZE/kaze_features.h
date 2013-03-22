#ifndef _KAZE_FEATURES_H_
#define _KAZE_FEATURES_H_

////////////////////////////////////////////////////////////////////
// Extract from ..\opencv\modules\features2d\src\precomp.hpp
//
#ifdef HAVE_CVCONFIG_H
#include "cvconfig.h"
#endif

#include "opencv2/features2d/features2d.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/imgproc/imgproc_c.h"
#include "opencv2/core/internal.hpp"

#include <algorithm>

#ifdef HAVE_TEGRA_OPTIMIZATION
#include "opencv2/features2d/features2d_tegra.hpp"
#endif
//
////////////////////////////////////////////////////////////////////

#include "kaze_config.h"

/*!
 KAZE features implementation.
 !! Note that it has NOT been warped to cv::Algorithm in oder to avoid rebuilding OpenCV
	So most functions of cv::Algorithm can not be used in cv::KAZE
 http://www.robesafe.com/personal/pablo.alcantarilla/papers/Alcantarilla12eccv.pdf
*/
namespace cv
{
	class CV_EXPORTS_W KAZE : public Feature2D
	{
	public:

		CV_WRAP explicit KAZE();
		KAZE(toptions &_options);

		// returns the descriptor size in bytes
		int descriptorSize() const;

		// returns the descriptor type
		int descriptorType() const;

		// Compute the KAZE features and descriptors on an image
		void operator()( InputArray image, InputArray mask, vector<KeyPoint>& keypoints,
			OutputArray descriptors, bool useProvidedKeypoints=false ) const;

		// Compute the KAZE features with mask
		void operator()(InputArray image, InputArray mask, vector<KeyPoint>& keypoints) const;

		// Compute the KAZE features and descriptors on an image WITHOUT mask
		void operator()(InputArray image, vector<KeyPoint>& keypoints, OutputArray descriptors) const;

		//AlgorithmInfo* info() const;

	protected:

		void detectImpl( const Mat& image, vector<KeyPoint>& keypoints, const Mat& mask=Mat() ) const;

		// !! NOT recommend to use because KAZE descriptors ONLY work with KAZE features
		void computeImpl( const Mat& image, vector<KeyPoint>& keypoints, Mat& descriptors ) const;

		CV_PROP_RW int nfeatures;

	private:
		toptions options;
	};

	typedef KAZE KazeFeatureDetector;
	//typedef KAZE KazeDescriptorExtractor;	// NOT available because KAZE descriptors ONLY work with KAZE features
}

#endif