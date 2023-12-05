/* -----------------------------------------------------------------
 * SUNDIALS Copyright Start
 * Copyright (c) 2002-2023, Lawrence Livermore National Security
 * and Southern Methodist University.
 * All rights reserved.
 *
 * See the top-level LICENSE and NOTICE files for details.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 * SUNDIALS Copyright End
 * -----------------------------------------------------------------*/

#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <nvector/nvector_serial.h>
#include <sundials/priv/sundials_errors_impl.h>
#include <sundials/sundials_core.h>
#include <sundials/sundials_nvector.h>

#include "sundials/sundials_context.h"
#include "sundials/sundials_errors.h"

class SUNErrConditionTest : public testing::Test
{
protected:
  SUNErrConditionTest()
  {
    SUNContext_Create(SUN_COMM_NULL, &sunctx);
    SUNContext_ClearErrHandlers(sunctx);
    SUNContext_PushErrHandler(sunctx, SUNLogErrHandlerFn, NULL);
    v = N_VNew_Serial(1, sunctx);
  }

  ~SUNErrConditionTest()
  {
    SUNContext_Free(&sunctx);
    N_VDestroy(v);
  }

  N_Vector v;
  SUNContext sunctx;
};

TEST_F(SUNErrConditionTest, GetLastErrorClearsErr)
{
  N_VCloneEmptyVectorArray(-1, v); // -1 is an out of range argument
  SUNErrCode err = SUNContext_GetLastError(sunctx);
  err            = SUNContext_GetLastError(sunctx);
  EXPECT_EQ(err, SUN_SUCCESS);
}

TEST_F(SUNErrConditionTest, PeekLastErrorKeepsErr)
{
  N_VCloneEmptyVectorArray(-1, v); // -1 is an out of range argument
  SUNErrCode err  = SUNContext_PeekLastError(sunctx);
  SUNErrCode err2 = SUNContext_GetLastError(sunctx);
  EXPECT_EQ(err, err2);
}

TEST_F(SUNErrConditionTest, LastErrConditionResultsInHandlerCalled)
{
  testing::internal::CaptureStderr();
  N_VCloneEmptyVectorArray(-1, v); // -1 is an out of range argument
  std::string output = testing::internal::GetCapturedStderr();
  EXPECT_THAT(output,
              testing::AllOf(testing::StartsWith("[ERROR]"),
                             testing::HasSubstr("[rank 0]"),
                             testing::HasSubstr("N_VCloneEmptyVectorArray")));
}

TEST_F(SUNErrConditionTest, LastErrConditionResultsInLastErrorSet)
{
  N_VCloneEmptyVectorArray(-1, v); // -1 is an out of range argument
  SUNErrCode err = SUNContext_GetLastError(sunctx);
  EXPECT_EQ(err, SUN_ERR_ARG_OUTOFRANGE);
}

TEST_F(SUNErrConditionTest, LastErrConditionPersists)
{
  N_VCloneEmptyVectorArray(-1, v); // -1 is an out of range argument
  SUNErrCode err = SUNContext_PeekLastError(sunctx);
  EXPECT_EQ(err, SUN_ERR_ARG_OUTOFRANGE);
  N_Vector* arr = N_VCloneEmptyVectorArray(1, v);
  EXPECT_FALSE(arr);
  err = SUNContext_GetLastError(sunctx);
  EXPECT_EQ(err, SUN_ERR_ARG_OUTOFRANGE);
  N_VDestroyVectorArray(arr, 1);
}

TEST_F(SUNErrConditionTest, ErrConditionResultsInErrReturned)
{
  SUNErrCode err = N_VCopyOps(v, NULL);
  EXPECT_EQ(err, SUN_ERR_ARG_CORRUPT);
}

TEST_F(SUNErrConditionTest, ErrConditionResultsInHandlerCalled)
{
  testing::internal::CaptureStderr();
  (void)N_VCopyOps(v, NULL);
  std::string output = testing::internal::GetCapturedStderr();
  EXPECT_THAT(output, testing::AllOf(testing::StartsWith("[ERROR]"),
                                     testing::HasSubstr("[rank 0]"),
                                     testing::HasSubstr("N_VCopyOps")));
}

class SUNErrHandlerFnTest : public testing::Test
{
protected:
  SUNErrHandlerFnTest() { SUNContext_Create(SUN_COMM_NULL, &sunctx); }

  ~SUNErrHandlerFnTest() { SUNContext_Free(&sunctx); }

  SUNContext sunctx;
};

TEST_F(SUNErrHandlerFnTest, SUNLogErrHandlerFnLogsWhenCalled)
{
  testing::internal::CaptureStderr();
  std::string message = "Test log handler";
  SUNLogErrHandlerFn(__LINE__, __func__, __FILE__, message.c_str(), -1, nullptr,
                     sunctx);
  std::string output = testing::internal::GetCapturedStderr();
  EXPECT_THAT(output, testing::AllOf(testing::StartsWith("[ERROR]"),
                                     testing::HasSubstr("[rank 0]"),
                                     testing::HasSubstr(__func__),
                                     testing::HasSubstr("Test log handler")));
}

TEST_F(SUNErrHandlerFnTest, SUNAbortErrHandlerFnAbortsWhenCalled)
{
  ASSERT_DEATH(
    {
      SUNAbortErrHandlerFn(__LINE__, __func__, __FILE__, "Test abort handler",
                           -1, nullptr, sunctx);
    },
    "SUNAbortErrHandler: Calling abort now, use a different error handler to "
    "avoid program termination.\n");
}

class SUNContextErrFunctionTests : public testing::Test
{
protected:
  SUNContextErrFunctionTests() { SUNContext_Create(SUN_COMM_NULL, &sunctx); }

  ~SUNContextErrFunctionTests() { SUNContext_Free(&sunctx); }

  SUNContext sunctx;
};

void firstHandler(int line, const char* func, const char* file, const char* msg,
                  SUNErrCode err_code, void* err_user_data, SUNContext sunctx)
{
  std::vector<int>* order = static_cast<std::vector<int>*>(err_user_data);
  order->push_back(0);
}

void secondHandler(int line, const char* func, const char* file, const char* msg,
                   SUNErrCode err_code, void* err_user_data, SUNContext sunctx)
{
  std::vector<int>* order = static_cast<std::vector<int>*>(err_user_data);
  order->push_back(1);
}

void thirdHandler(int line, const char* func, const char* file, const char* msg,
                  SUNErrCode err_code, void* err_user_data, SUNContext sunctx)
{
  std::vector<int>* order = static_cast<std::vector<int>*>(err_user_data);
  order->push_back(2);
}

TEST_F(SUNContextErrFunctionTests, SUNContextPushErrHandlerWorks)
{
  std::vector<int> order = {};
  SUNContext_ClearErrHandlers(sunctx);
  SUNContext_PushErrHandler(sunctx, firstHandler, static_cast<void*>(&order));
  SUNContext_PushErrHandler(sunctx, secondHandler, static_cast<void*>(&order));
  SUNContext_PushErrHandler(sunctx, thirdHandler, static_cast<void*>(&order));
  SUNHandleErrWithMsg(__LINE__, __func__, __FILE__, NULL, -1, sunctx);
  EXPECT_EQ(order.size(), 3);
  EXPECT_EQ(order.at(0), 2);
  EXPECT_EQ(order.at(1), 1);
  EXPECT_EQ(order.at(2), 0);
}

TEST_F(SUNContextErrFunctionTests, SUNContextPopErrHandlerWorks)
{
  std::vector<int> order = {};
  SUNContext_ClearErrHandlers(sunctx);
  SUNContext_PushErrHandler(sunctx, firstHandler, static_cast<void*>(&order));
  SUNContext_PushErrHandler(sunctx, secondHandler, static_cast<void*>(&order));
  SUNContext_PushErrHandler(sunctx, thirdHandler, static_cast<void*>(&order));
  SUNContext_PopErrHandler(sunctx);
  SUNHandleErrWithMsg(__LINE__, __func__, __FILE__, NULL, -1, sunctx);
  EXPECT_EQ(order.size(), 2);
  EXPECT_EQ(order.at(0), 1);
  EXPECT_EQ(order.at(1), 0);
}
