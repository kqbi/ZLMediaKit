﻿/*
 * Copyright (c) 2016 The ZLMediaKit project authors. All Rights Reserved.
 *
 * This file is part of ZLMediaKit(https://github.com/xiongziliang/ZLMediaKit).
 *
 * Use of this source code is governed by MIT license that can be found in the
 * LICENSE file in the root of the source tree. All contributing project authors
 * may be found in the AUTHORS file in the root of the source tree.
 */

#include "RtpCache.h"

#if defined(ENABLE_RTPPROXY)

namespace mediakit{

RtpCache::RtpCache(onFlushed cb) {
    _cb = std::move(cb);
}

void RtpCache::onFlush(std::shared_ptr<List<Buffer::Ptr> > rtp_list, bool) {
    _cb(std::move(rtp_list));
}

void RtpCache::input(uint64_t stamp, Buffer::Ptr buffer) {
    inputPacket(stamp, true, std::move(buffer), false);
}

void RtpCachePS::onRTP(Buffer::Ptr buffer) {
    auto rtp = static_pointer_cast<RtpPacket>(buffer);
    auto stamp = rtp->timeStamp;
    input(stamp, std::move(buffer));
}

}//namespace mediakit

#endif//#if defined(ENABLE_RTPPROXY)