#ifndef GUARD_MLOPEN_CONVOLUTION_HPP_
#define GUARD_MLOPEN_CONVOLUTION_HPP_

#include <mlopen.h>
#include <mlopen/handle.hpp>
#include <mlopen/tensor.hpp>
#include <mlopen/common.hpp>

namespace mlopen {

struct ConvolutionDescriptor : mlopenConvolutionDescriptor {
	
	ConvolutionDescriptor(int p_pad_h = 0, int p_pad_w = 0, int p_u = 1, int p_v = 1, int p_upscalex = 1, int p_upscaley = 1);
	ConvolutionDescriptor(mlopenConvolutionMode_t p_mode, int p_pad_h = 0, int p_pad_w = 0, int p_u = 1, int p_v = 1, int p_upscalex = 1, int p_upscaley = 1);

	std::tuple<int, int, int, int> GetForwardOutputDim(const TensorDescriptor& inputTensorDesc,
										const TensorDescriptor& filterDesc) const;
	TensorDescriptor GetForwardOutputTensor(const TensorDescriptor& inputTensorDesc,
										const TensorDescriptor& filterDesc) const;

	void FindConvFwdAlgorithm(Handle& handle,
		const TensorDescriptor&			xDesc,
		ConstData_t						x,
		const TensorDescriptor&			wDesc,
		ConstData_t						w,
		const TensorDescriptor&			yDesc,
		ConstData_t						y,
		int						requestAlgoCount,
		int								*returnedAlgoCount,
		mlopenConvAlgoPerf_t			*perfResults,
		mlopenConvPreference_t			preference,
		void							*workSpace,
		size_t							workSpaceSize,
		bool							exhaustiveSearch) const;

	void ConvolutionForward(Handle& handle,
		const void						*alpha,
		const TensorDescriptor&			xDesc,
		ConstData_t						x,
		const TensorDescriptor&			wDesc,
		ConstData_t						w,
		mlopenConvFwdAlgorithm_t		algo,
		const void						*beta,
		const TensorDescriptor&			yDesc,
		Data_t							y,
		void							*workSpace,
		size_t							workSpaceSize) const;

	void FindConvBwdDataAlgorithm(Handle& handle,
		const TensorDescriptor&			dyDesc,
		ConstData_t						dy,
		const TensorDescriptor&			wDesc,
		ConstData_t						w,
		const TensorDescriptor&			dxDesc,
		ConstData_t						dx,
		int						requestAlgoCount,
		int								*returnedAlgoCount,
		mlopenConvAlgoPerf_t			*perfResults,
		mlopenConvPreference_t			preference,
		void							*workSpace,
		size_t							workSpaceSize,
		bool							exhaustiveSearch) const;

	void ConvolutionBackwardData(Handle& handle,
		const void						*alpha,
		const TensorDescriptor&			dyDesc,
		ConstData_t						dy,
		const TensorDescriptor&			wDesc,
		ConstData_t						w,
		mlopenConvBwdDataAlgorithm_t	algo,
		const void						*beta,
		const TensorDescriptor&			dxDesc,
		Data_t							dx,
		void							*workSpace,
		size_t							workSpaceSize) const;

	mlopenConvolutionMode_t mode;
	int pad_h;
	int pad_w;
	int u;
	int v;
	int upscalex;
	int upscaley;
};
}  // namespace mlopen
MLOPEN_DEFINE_OBJECT(mlopenConvolutionDescriptor, mlopen::ConvolutionDescriptor);

#endif // GUARD_MLOPEN_CONVOLUTION_HPP_