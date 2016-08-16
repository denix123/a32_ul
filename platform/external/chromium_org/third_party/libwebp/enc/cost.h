// Copyright 2011 Google Inc. All Rights Reserved.
// Use of this source code is governed by a BSD-style license

#ifndef WEBP_ENC_COST_H_
#define WEBP_ENC_COST_H_

#include <assert.h>
#include <stdlib.h>
#include "./vp8enci.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
  int first;
  int last;
  const int16_t* coeffs;

  int coeff_type;
  ProbaArray* prob;
  StatsArray* stats;
  CostArray*  cost;
} VP8Residual;

void VP8InitResidual(int first, int coeff_type,
                     VP8Encoder* const enc, VP8Residual* const res);

typedef void (*VP8SetResidualCoeffsFunc)(const int16_t* const coeffs,
                                         VP8Residual* const res);
extern VP8SetResidualCoeffsFunc VP8SetResidualCoeffs;

extern void VP8SetResidualCoeffsInit(void);  

int VP8RecordCoeffs(int ctx, const VP8Residual* const res);

extern const uint16_t VP8LevelFixedCosts[MAX_LEVEL + 1];
extern const uint16_t VP8EntropyCost[256];        

static WEBP_INLINE int VP8BitCost(int bit, uint8_t proba) {
  return !bit ? VP8EntropyCost[proba] : VP8EntropyCost[255 - proba];
}

typedef int (*VP8GetResidualCostFunc)(int ctx0, const VP8Residual* const res);
extern VP8GetResidualCostFunc VP8GetResidualCost;

extern void VP8GetResidualCostInit(void);  

extern const uint16_t VP8LevelCodes[MAX_VARIABLE_LEVEL][2];
void VP8CalculateLevelCosts(VP8Proba* const proba);
static WEBP_INLINE int VP8LevelCost(const uint16_t* const table, int level) {
  return VP8LevelFixedCosts[level]
       + table[(level > MAX_VARIABLE_LEVEL) ? MAX_VARIABLE_LEVEL : level];
}

extern const uint16_t VP8FixedCostsUV[4];
extern const uint16_t VP8FixedCostsI16[4];
extern const uint16_t VP8FixedCostsI4[NUM_BMODES][NUM_BMODES][NUM_BMODES];


#ifdef __cplusplus
}    
#endif

#endif  