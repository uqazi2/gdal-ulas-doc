/**********************************************************************
 *
 * Project:  CPL - Common Portability Library
 * Purpose:  Implementation of quadtree building and searching functions.
 *           Derived from shapelib and mapserver implementations
 * Author:   Frank Warmerdam, warmerdam@pobox.com
 *           Even Rouault, <even dot rouault at spatialys.com>
 *
 ******************************************************************************
 * Copyright (c) 1999-2008, Frank Warmerdam
 * Copyright (c) 2008-2014, Even Rouault <even dot rouault at spatialys.com>
 *
 * SPDX-License-Identifier: MIT
 ****************************************************************************/

#ifndef CPL_QUAD_TREE_H_INCLUDED
#define CPL_QUAD_TREE_H_INCLUDED

#include "cpl_port.h"

#include <stdbool.h>

/**
 * \file cpl_quad_tree.h
 *
 * Quad tree implementation.
 *
 * A quadtree is a tree data structure in which each internal node
 * has up to four children. Quadtrees are most often used to partition
 * a two dimensional space by recursively subdividing it into four
 * quadrants or regions
 */

CPL_C_START

/* Types */

/** Describe a rectangle */
typedef struct
{
    double minx; /**< Minimum x */
    double miny; /**< Minimum y */
    double maxx; /**< Maximum x */
    double maxy; /**< Maximum y */
} CPLRectObj;

/** Opaque type for a quad tree */
typedef struct _CPLQuadTree CPLQuadTree;

/** CPLQuadTreeGetBoundsFunc */
typedef void (*CPLQuadTreeGetBoundsFunc)(const void *hFeature,
                                         CPLRectObj *pBounds);
/** CPLQuadTreeGetBoundsExFunc */
typedef void (*CPLQuadTreeGetBoundsExFunc)(const void *hFeature,
                                           void *pUserData,
                                           CPLRectObj *pBounds);
/** CPLQuadTreeForeachFunc */
typedef int (*CPLQuadTreeForeachFunc)(void *pElt, void *pUserData);
/** CPLQuadTreeDumpFeatureFunc */
typedef void (*CPLQuadTreeDumpFeatureFunc)(const void *hFeature,
                                           int nIndentLevel, void *pUserData);

/* Functions */

CPLQuadTree CPL_DLL *CPLQuadTreeCreate(const CPLRectObj *pGlobalBounds,
                                       CPLQuadTreeGetBoundsFunc pfnGetBounds);
CPLQuadTree CPL_DLL *
CPLQuadTreeCreateEx(const CPLRectObj *pGlobalBounds,
                    CPLQuadTreeGetBoundsExFunc pfnGetBounds, void *pUserData);
void CPL_DLL CPLQuadTreeDestroy(CPLQuadTree *hQuadtree);

void CPL_DLL CPLQuadTreeSetBucketCapacity(CPLQuadTree *hQuadtree,
                                          int nBucketCapacity);
void CPL_DLL CPLQuadTreeForceUseOfSubNodes(CPLQuadTree *hQuadTree);
int CPL_DLL CPLQuadTreeGetAdvisedMaxDepth(int nExpectedFeatures);
void CPL_DLL CPLQuadTreeSetMaxDepth(CPLQuadTree *hQuadtree, int nMaxDepth);

void CPL_DLL CPLQuadTreeInsert(CPLQuadTree *hQuadtree, void *hFeature);
void CPL_DLL CPLQuadTreeInsertWithBounds(CPLQuadTree *hQuadtree, void *hFeature,
                                         const CPLRectObj *psBounds);

void CPL_DLL CPLQuadTreeRemove(CPLQuadTree *hQuadtree, void *hFeature,
                               const CPLRectObj *psBounds);

void CPL_DLL **CPLQuadTreeSearch(const CPLQuadTree *hQuadtree,
                                 const CPLRectObj *pAoi, int *pnFeatureCount);

bool CPL_DLL CPLQuadTreeHasMatch(const CPLQuadTree *hQuadtree,
                                 const CPLRectObj *pAoi);

void CPL_DLL CPLQuadTreeForeach(const CPLQuadTree *hQuadtree,
                                CPLQuadTreeForeachFunc pfnForeach,
                                void *pUserData);

void CPL_DLL CPLQuadTreeDump(const CPLQuadTree *hQuadtree,
                             CPLQuadTreeDumpFeatureFunc pfnDumpFeatureFunc,
                             void *pUserData);
void CPL_DLL CPLQuadTreeGetStats(const CPLQuadTree *hQuadtree,
                                 int *pnFeatureCount, int *pnNodeCount,
                                 int *pnMaxDepth, int *pnMaxBucketCapacity);

CPL_C_END

#endif
