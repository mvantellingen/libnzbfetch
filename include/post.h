/*
 * Copyright (c) 2004-2007 Michael van Tellingen.  All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. The name of the author may not be used to endorse or promote products
 *    derived from this software without specific prior written permission
 *    
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
 * NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef _POST_H
#define _POST_H

#include <pthread.h>

#include "server.h"
#include "segment.h"
#include "queue.h"

#define FILE_COMPLETE   0x01


#define SEGMENT_NEW             2
#define SEGMENT_ERROR           4
#define SEGMENT_COMPLETE        8


/*!
 * Fileinfo type contains the filename and other unused variables
 */
typedef struct fileinfo_s
{
    char *filename;         //!< Filename
    int num_segments;
    
    unsigned int flags;
    
} fileinfo_t;




/*!
 * A post can exists out of multiple segments and generaly represents one file.
 */
typedef struct post_s
{
    int id;
    char *subject;
    fileinfo_t *fileinfo;

    int num_groups;         // Number of groups
    char **groups;          // Array with groups

    int num_segments;               //!< Number of segments
    struct segment_s **segments;    //!< Array with segments
    int *segments_status;           //!< Flags for the segment status
    int *segments_;
    
    struct post_s *next, *prev;
} post_t;


struct connection_thread
{
    int thread_num;
    int ready;

    int sock;                         //!< Socket

    struct queue_list_s **queues;     //!< Array of queues with empy segments
    struct queue_list_s *data_queue;  //!< Pointer to queue with full segments
    pthread_t thread_id;
    struct server_s *server;
    //postlist_t *postlist;
};




//void types_postlist_init(postlist_t *postlist);

void types_free_post(post_t *post);
post_t * types_create_post();

fileinfo_t * types_create_fileinfo();
void types_free_fileinfo(fileinfo_t *fileinfo);

void types_post_remove(post_t *target, post_t *post);
void types_post_insert(post_t *target, post_t *post);

#endif