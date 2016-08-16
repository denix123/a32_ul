/* Copyright (c) 2012 The Chromium Authors. All rights reserved.
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */

#include "queue.h"

#include <pthread.h>
#include <stdlib.h>

#include "ppapi/c/pp_var.h"

#define MAX_QUEUE_SIZE 16

static pthread_mutex_t g_queue_mutex;

static pthread_cond_t g_queue_not_empty_cond;

static struct PP_Var g_queue[MAX_QUEUE_SIZE];

static int g_queue_start = 0;

static int g_queue_end = 0;

static int g_queue_size = 0;

static int IsQueueEmpty() { return g_queue_size == 0; }

static int IsQueueFull() { return g_queue_size == MAX_QUEUE_SIZE; }

void InitializeMessageQueue() {
  pthread_mutex_init(&g_queue_mutex, NULL);
  pthread_cond_init(&g_queue_not_empty_cond, NULL);
}

int EnqueueMessage(struct PP_Var message) {
  pthread_mutex_lock(&g_queue_mutex);

  if (IsQueueFull()) {
    pthread_mutex_unlock(&g_queue_mutex);
    return 0;
  }

  g_queue[g_queue_end] = message;
  g_queue_end = (g_queue_end + 1) % MAX_QUEUE_SIZE;
  g_queue_size++;

  pthread_cond_signal(&g_queue_not_empty_cond);

  pthread_mutex_unlock(&g_queue_mutex);

  return 1;
}

struct PP_Var DequeueMessage() {
  struct PP_Var message;

  pthread_mutex_lock(&g_queue_mutex);

  while (IsQueueEmpty()) {
    pthread_cond_wait(&g_queue_not_empty_cond, &g_queue_mutex);
  }

  message = g_queue[g_queue_start];
  g_queue_start = (g_queue_start + 1) % MAX_QUEUE_SIZE;
  g_queue_size--;

  pthread_mutex_unlock(&g_queue_mutex);

  return message;
}
