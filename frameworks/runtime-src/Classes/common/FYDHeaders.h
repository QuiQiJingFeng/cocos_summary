//
//  FYDHeaders.h
//  Email
//
//  Created by JingFeng on 2018/6/23.
//  Copyright © 2018年 JingFeng. All rights reserved.
//

#ifndef FYDHeaders_h
#define FYDHeaders_h

#define NS_FYD_BEGIN namespace FYD {
#define NS_FYD_ENDED }
#define USING_NS_FYD using namespace FYD;


#include <assert.h>

#define FYDASSERT(cond,msg) do {\
    if (!(cond)) {\
        if (msg) {\
            printf("Assert failed: %s\n", msg);\
        }\
        assert(cond);\
    } \
} while (0)


#define FYD_SAFE_DELETE(p)           do { delete (p); (p) = nullptr; } while(0)
#define FYD_SAFE_DELETE_ARRAY(p)     do { if(p) { delete[] (p); (p) = nullptr; } } while(0)
#define FYD_SAFE_FREE(p)             do { if(p) { free(p); (p) = nullptr; } } while(0)

#endif /* FYDHeaders_h */
