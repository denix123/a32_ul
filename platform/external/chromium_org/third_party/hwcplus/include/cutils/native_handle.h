/*
 * Copyright (C) 2009 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef NATIVE_HANDLE_H_
#define NATIVE_HANDLE_H_

#ifdef __cplusplus
extern "C" {
#endif

typedef struct native_handle
{
    int version;        
    int numFds;         
    int numInts;        
    int data[0];        
} native_handle_t;

int native_handle_close(const native_handle_t* h);


native_handle_t* native_handle_create(int numFds, int numInts);

int native_handle_delete(native_handle_t* h);


#ifdef __cplusplus
}
#endif

#endif 
