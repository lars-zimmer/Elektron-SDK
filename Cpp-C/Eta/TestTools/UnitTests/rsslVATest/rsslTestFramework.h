/*|-----------------------------------------------------------------------------
 *|            This source code is provided under the Apache 2.0 license      --
 *|  and is provided AS IS with no warranty or guarantee of fit for purpose.  --
 *|                See the project's LICENSE.md for details.                  --
 *|           Copyright Thomson Reuters 2018. All rights reserved.            --
 *|-----------------------------------------------------------------------------
 */

#ifndef RSSLTEST_FRAMEWORK_H
#define RSSLTEST_FRAMEWORK_H 

#include "rtr/rsslTransport.h"
#include "testFramework.h"
#include "rtr/rsslRDMMsg.h"
#include "rtr/rsslMessagePackage.h"
#include "gtest/gtest.h"
#include <assert.h>

#define EXPECT_FALSE_RET_IF_FAILED(condition,text,retVal) \
	EXPECT_FALSE(condition); \
	if (condition) \
	{ \
		printf("Error text : %s\n", text); \
		return retVal; \
	} \

#ifdef __cplusplus
extern "C" {
#endif

// add more options as we need them
typedef struct
{
	RsslConnectionTypes connectionType;
} rsslTestInitOpts;

// any added options need to be cleared in this function
static void rsslTestClearInitOpts(rsslTestInitOpts *pOpts)
{
	pOpts->connectionType = RSSL_CONN_TYPE_SOCKET;
}


// Call before starting a series of tests. 
void rsslTestInitialize(rsslTestInitOpts *pOpts);

// Call after finishing a series of tests. 
void rsslTestUninitialize();

// Call before starting a single test.
#define rsslTestStart() { rssl_test_start(); }

// Call when finishing a single test.
#define rsslTestFinish() { rssl_test_finish(); }


/*** Connections ***/
RsslChannel *rsslTestCreateConsumerChannel();
RsslChannel *rsslTestCreateProviderChannel();
void rsslTestInitChannels(RsslChannel *provChannel, RsslChannel *consChannel);

RsslRet sendMessage(RsslChannel *pchannel, RsslBuffer *msgBuf);
RsslRet sendLoginRequest(RsslChannel *pchannel, RsslInt32 streamId);
RsslRet sendDictionaryRequests(RsslChannel *pchannel, RsslUInt16 serviceId, 
		RsslInt32 fieldDictionaryStreamId, RsslInt32 enumTypeDictionaryStreamId);
RsslRet sendDirectoryRequest(RsslChannel *pChannel, RsslInt32 streamId);
RsslRet processLoginRequest(RsslChannel *pChannel, RsslMsg* msg, RsslDecodeIterator* dIter);

#ifdef __cplusplus
};
#endif

#endif