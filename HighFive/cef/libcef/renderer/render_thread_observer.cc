/// Copyright (c) 2013 The Chromium Embedded Framework Authors.
// Portions (c) 2011 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "libcef/renderer/render_thread_observer.h"
#include "libcef/common/cef_messages.h"
#include "libcef/common/net/net_resource_provider.h"
#include "libcef/renderer/content_renderer_client.h"

#include "net/base/net_module.h"
#include "third_party/WebKit/public/platform/WebString.h"
#include "third_party/WebKit/public/platform/WebURL.h"
#include "third_party/WebKit/public/web/WebSecurityPolicy.h"

bool CefRenderThreadObserver::is_incognito_process_ = false;

CefRenderThreadObserver::CefRenderThreadObserver() {
  net::NetModule::SetResourceProvider(NetResourceProvider);
}

CefRenderThreadObserver::~CefRenderThreadObserver() {
}

bool CefRenderThreadObserver::OnControlMessageReceived(
    const IPC::Message& message) {
  bool handled = true;
  IPC_BEGIN_MESSAGE_MAP(CefRenderThreadObserver, message)
    IPC_MESSAGE_HANDLER(CefProcessMsg_SetIsIncognitoProcess,
                        OnSetIsIncognitoProcess)
    IPC_MESSAGE_HANDLER(CefProcessMsg_ModifyCrossOriginWhitelistEntry,
                        OnModifyCrossOriginWhitelistEntry)
    IPC_MESSAGE_HANDLER(CefProcessMsg_ClearCrossOriginWhitelist,
                        OnClearCrossOriginWhitelist)
    IPC_MESSAGE_UNHANDLED(handled = false)
  IPC_END_MESSAGE_MAP()
  return handled;
}

void CefRenderThreadObserver::OnRenderProcessShutdown() {
  CefContentRendererClient::Get()->OnRenderProcessShutdown();
}

void CefRenderThreadObserver::OnSetIsIncognitoProcess(
    bool is_incognito_process) {
  is_incognito_process_ = is_incognito_process;
}

void CefRenderThreadObserver::OnModifyCrossOriginWhitelistEntry(
    bool add,
    const Cef_CrossOriginWhiteListEntry_Params& params) {
  GURL gurl = GURL(params.source_origin);
  if (add) {
    blink::WebSecurityPolicy::addOriginAccessWhitelistEntry(
        gurl,
        blink::WebString::fromUTF8(params.target_protocol),
        blink::WebString::fromUTF8(params.target_domain),
        params.allow_target_subdomains);
  } else {
    blink::WebSecurityPolicy::removeOriginAccessWhitelistEntry(
        gurl,
        blink::WebString::fromUTF8(params.target_protocol),
        blink::WebString::fromUTF8(params.target_domain),
        params.allow_target_subdomains);
  }
}

void CefRenderThreadObserver::OnClearCrossOriginWhitelist() {
  blink::WebSecurityPolicy::resetOriginAccessWhitelists();
}
