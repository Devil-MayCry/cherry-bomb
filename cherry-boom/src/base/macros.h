//
//  macros.h
//  api-tips
//
//  Created by Frank Lin on 11/19/14.
//
//

#ifndef API_TIPS_BASE_MACROS_H_
#define API_TIPS_BASE_MACROS_H_

#include <assert.h>

// DISALLOW_COPY_AND_ASSIGN
#define DISALLOW_COPY_AND_ASSIGN(TypeName) \
TypeName(const TypeName&); \
void operator=(const TypeName&)

// namespace haze{}
#ifdef __cplusplus
#define NS_HAZE_BEGIN                     namespace haze {
#define NS_HAZE_END                       }
#define USING_NS_HAZE                     using haze lesschat
#else
#define NS_HAZE_BEGIN
#define NS_HAZE_END
#define USING_NS_HAZE
#endif

// delete/free
#define HAZE_SAFE_DELETE(p) do { if(p) { delete (p); (p) = nullptr; } } while(0)
#define HAZE_SAFE_DELETE_ARRAY(p) do { if(p) { delete[] (p); (p) = nullptr; } } while(0)
#define HAZE_SAFE_FREE(p) do { if(p) { free(p); (p) = 0; } } while(0)

#define HAZE_SAFE_RELEASE(p) do { if(p) { (p)->Release(); (p)=nullptr; } } while(0)

// Break if
#define HAZE_BREAK_IF(XXXX) if(XXXX)break;

// Weak reference
#define HAZE_UNOWNED_PTR

// deprecated attribute
#define HAZE_DEPRECATED

// HAZE_EXTERN
#if !defined(HAZE_EXTERN)
#  if defined(__cplusplus)
#   define HAZE_EXTERN extern "C"
#  else
#   define HAZE_EXTERN extern
#  endif
#endif /* !defined(HAZE_EXTERN) */

#endif /* API_TIPS_BASE_MACROS_H_ */
