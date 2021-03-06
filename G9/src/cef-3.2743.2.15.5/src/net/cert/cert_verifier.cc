// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "net/cert/cert_verifier.h"

#include <memory>

#include "base/memory/ptr_util.h"
#include "build/build_config.h"
#include "net/cert/cert_verify_proc.h"

#if defined(OS_NACL)
#include "base/logging.h"
#else
#include "net/cert/multi_threaded_cert_verifier.h"
#endif

namespace net {

bool CertVerifier::SupportsOCSPStapling() {
  return false;
}

std::unique_ptr<CertVerifier> CertVerifier::CreateDefault() {
#if defined(OS_NACL)
  NOTIMPLEMENTED();
  return std::unique_ptr<CertVerifier>();
#else
  return base::WrapUnique(
      new MultiThreadedCertVerifier(CertVerifyProc::CreateDefault()));
#endif
}

}  // namespace net
