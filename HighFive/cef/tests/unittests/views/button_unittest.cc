// Copyright (c) 2016 The Chromium Embedded Framework Authors. All rights
// reserved. Use of this source code is governed by a BSD-style license that
// can be found in the LICENSE file.

#include "include/views/cef_button.h"
#include "include/views/cef_button_delegate.h"
#include "include/views/cef_label_button.h"
#include "include/views/cef_menu_button.h"
#include "include/views/cef_menu_button_delegate.h"
#include "include/wrapper/cef_closure_task.h"
#include "tests/unittests/image_util.h"
#include "tests/unittests/thread_helper.h"
#include "tests/unittests/views/test_window_delegate.h"

#include "base/bind.h"
#include "testing/gtest/include/gtest/gtest.h"

#define BUTTON_TEST(name) UI_THREAD_TEST(ViewsButtonTest, name)
#define BUTTON_TEST_ASYNC(name) UI_THREAD_TEST_ASYNC(ViewsButtonTest, name)

namespace {

CefRefPtr<CefImage> CreateIconImage() {
  CefRefPtr<CefImage> image = CefImage::CreateImage();
  image_util::LoadIconImage(image, 1.0);
  image_util::LoadIconImage(image, 2.0);
  return image;
}

const char kButtonText[] = "My Button";

void VerifyButtonStyle(CefRefPtr<CefButton> button) {
  // Test state.
  EXPECT_EQ(CEF_BUTTON_STATE_NORMAL, button->GetState());
  button->SetState(CEF_BUTTON_STATE_HOVERED);
  EXPECT_EQ(CEF_BUTTON_STATE_HOVERED, button->GetState());
  button->SetState(CEF_BUTTON_STATE_PRESSED);
  EXPECT_EQ(CEF_BUTTON_STATE_PRESSED, button->GetState());
  button->SetState(CEF_BUTTON_STATE_DISABLED);
  EXPECT_EQ(CEF_BUTTON_STATE_DISABLED, button->GetState());
  button->SetState(CEF_BUTTON_STATE_NORMAL);

  button->SetTooltipText("Some tooltip text");
  button->SetAccessibleName("MyButton");
}

void VerifyLabelButtonImage(CefRefPtr<CefLabelButton> button,
                            cef_button_state_t state,
                            CefRefPtr<CefImage> image) {
  EXPECT_FALSE(button->GetImage(state).get()) << "state = " << state;
  button->SetImage(state, image);
  EXPECT_TRUE(image->IsSame(button->GetImage(state))) << "state = " << state;
  button->SetImage(state, nullptr);
  EXPECT_FALSE(button->GetImage(state).get()) << "state = " << state;
}

void VerifyLabelButtonStyle(CefRefPtr<CefLabelButton> button) {
  VerifyButtonStyle(button);

  // Test set/get text.
  EXPECT_STREQ(kButtonText, button->GetText().ToString().c_str());
  const char kText[] = "My text";
  button->SetText(kText);
  EXPECT_STREQ(kText, button->GetText().ToString().c_str());

  // Test images.
  CefRefPtr<CefImage> image = CreateIconImage();
  VerifyLabelButtonImage(button, CEF_BUTTON_STATE_NORMAL, image);
  VerifyLabelButtonImage(button, CEF_BUTTON_STATE_HOVERED, image);
  VerifyLabelButtonImage(button, CEF_BUTTON_STATE_PRESSED, image);
  VerifyLabelButtonImage(button, CEF_BUTTON_STATE_DISABLED, image);

  // Test colors.
  const cef_color_t color = CefColorSetARGB(255, 255, 0, 255);
  button->SetTextColor(CEF_BUTTON_STATE_NORMAL, color);
  button->SetTextColor(CEF_BUTTON_STATE_HOVERED, color);
  button->SetTextColor(CEF_BUTTON_STATE_PRESSED, color);
  button->SetTextColor(CEF_BUTTON_STATE_DISABLED, color);
  button->SetEnabledTextColors(color);

  // Test alignment.
  button->SetHorizontalAlignment(CEF_HORIZONTAL_ALIGNMENT_LEFT);
  button->SetHorizontalAlignment(CEF_HORIZONTAL_ALIGNMENT_CENTER);
  button->SetHorizontalAlignment(CEF_HORIZONTAL_ALIGNMENT_RIGHT);

  // Test fonts.
  button->SetFontList("Arial, 14px");

  // Test sizes.
  button->SetMinimumSize(CefSize(100, 100));
  button->SetMaximumSize(CefSize(100, 100));
}

void VerifyMenuButtonStyle(CefRefPtr<CefMenuButton> button) {
  VerifyLabelButtonStyle(button);
}

class EmptyMenuButtonDelegate : public CefMenuButtonDelegate {
 public:
  EmptyMenuButtonDelegate() {
  }

  void OnMenuButtonPressed(CefRefPtr<CefMenuButton> menu_button,
                           const CefPoint& screen_point) override {
    EXPECT_TRUE(false);  // Not reached.
  }

  void OnButtonPressed(CefRefPtr<CefButton> button) override {
    EXPECT_TRUE(false);  // Not reached.
  }

 private:
  IMPLEMENT_REFCOUNTING(EmptyMenuButtonDelegate);
  DISALLOW_COPY_AND_ASSIGN(EmptyMenuButtonDelegate);
};

void LabelButtonStyle(bool with_frame) {
  CefRefPtr<CefLabelButton> button =
      CefLabelButton::CreateLabelButton(new EmptyMenuButtonDelegate(),
                                        kButtonText, with_frame);
  VerifyLabelButtonStyle(button);
}

void LabelButtonStyleFramedImpl() {
  LabelButtonStyle(true);
}

void LabelButtonStyleFramelessImpl() {
  LabelButtonStyle(false);
}

void MenuButtonStyle(bool with_frame, bool with_menu_marker) {
  CefRefPtr<CefMenuButton> button =
      CefMenuButton::CreateMenuButton(new EmptyMenuButtonDelegate(),
                                      kButtonText, with_frame,
                                      with_menu_marker);
  VerifyMenuButtonStyle(button);
}

void MenuButtonStyleFramedWithMarkerImpl() {
  MenuButtonStyle(true, true);
}

void MenuButtonStyleFramedNoMarkerImpl() {
  MenuButtonStyle(true, false);
}

void MenuButtonStyleFramelessWithMarkerImpl() {
  MenuButtonStyle(false, true);
}

void MenuButtonStyleFramelessNoMarkerImpl() {
  MenuButtonStyle(false, false);
}

}  // namespace

// Test Button getters/setters.
BUTTON_TEST(LabelButtonStyleFramed);
BUTTON_TEST(LabelButtonStyleFrameless);
BUTTON_TEST(MenuButtonStyleFramedWithMarker);
BUTTON_TEST(MenuButtonStyleFramedNoMarker);
BUTTON_TEST(MenuButtonStyleFramelessWithMarker);
BUTTON_TEST(MenuButtonStyleFramelessNoMarker);


namespace {

// Mouse click delay in MS.
const int kClickDelayMS = 100;

const int kButtonID = 1;

class TestButtonDelegate : public CefButtonDelegate {
 public:
  TestButtonDelegate() {
  }

  void OnButtonPressed(CefRefPtr<CefButton> button) override {
    EXPECT_TRUE(button.get());
    EXPECT_EQ(button->GetID(), kButtonID);

    // Complete the test by closing the window.
    button->GetWindow()->Close();
  }

 private:
  IMPLEMENT_REFCOUNTING(TestButtonDelegate);
  DISALLOW_COPY_AND_ASSIGN(TestButtonDelegate);
};

void ClickButton(CefRefPtr<CefWindow> window, int button_id) {
  CefRefPtr<CefView> button = window->GetViewForID(button_id);
  EXPECT_TRUE(button->AsButton());

  // Determine the middle of the button in screen coordinates.
  const CefRect& bounds = button->GetBoundsInScreen();
  const CefPoint& click_point = CefPoint(bounds.x + bounds.width / 2,
                                         bounds.y + bounds.height / 2);

  // Click the button.
  window->SendMouseMove(click_point.x, click_point.y);
  window->SendMouseEvents(MBT_LEFT, true, true);
}

void AddImage(CefRefPtr<CefLabelButton> button) {
  CefRefPtr<CefImage> image = CreateIconImage();
  button->SetImage(CEF_BUTTON_STATE_NORMAL, image);
}

void RunLabelButtonClick(bool with_frame,
                         bool with_text,
                         bool with_image,
                         CefRefPtr<CefWindow> window) {
  CefRefPtr<CefLabelButton> button = CefLabelButton::CreateLabelButton(
      new TestButtonDelegate(), with_text ? kButtonText : "", with_frame);
  button->SetID(kButtonID);

  EXPECT_TRUE(button->AsButton());
  EXPECT_TRUE(button->AsButton()->AsLabelButton());
  EXPECT_EQ(kButtonID, button->GetID());
  EXPECT_TRUE(button->IsVisible());
  EXPECT_FALSE(button->IsDrawn());

  if (with_text)
    EXPECT_STREQ(kButtonText, button->GetText().ToString().c_str());
  else
    EXPECT_TRUE(button->GetText().empty());

  if (with_image)
    AddImage(button);

  window->AddChildView(button);
  window->Layout();

  EXPECT_TRUE(window->IsSame(button->GetWindow()));
  EXPECT_TRUE(window->IsSame(button->GetParentView()));
  EXPECT_TRUE(button->IsSame(window->GetViewForID(kButtonID)));
  EXPECT_TRUE(button->IsVisible());
  EXPECT_TRUE(button->IsDrawn());

  window->Show();

  // Wait a bit before trying to click the button.
  CefPostDelayedTask(TID_UI, base::Bind(ClickButton, window, kButtonID),
                     kClickDelayMS);
}

void LabelButtonClick(base::WaitableEvent* event,
                      bool with_button_frame,
                      bool with_button_text,
                      bool with_button_image,
                      bool with_window_frame) {
  TestWindowDelegate::RunTest(event,
      base::Bind(RunLabelButtonClick, with_button_frame, with_button_text,
                 with_button_image),
      !with_window_frame, false);
}

void LabelButtonClickFramedWithTextWithImageFramedWindowImpl(
    base::WaitableEvent* event) {
  LabelButtonClick(event, true, true, true, true);
}

void LabelButtonClickFramedWithTextNoImageFramedWindowImpl(
    base::WaitableEvent* event) {
  LabelButtonClick(event, true, true, false, true);
}

void LabelButtonClickFramedWithTextWithImageFramelessWindowImpl(
    base::WaitableEvent* event) {
  LabelButtonClick(event, true, true, true, false);
}

void LabelButtonClickFramedWithTextNoImageFramelessWindowImpl(
    base::WaitableEvent* event) {
  LabelButtonClick(event, true, true, false, false);
}

void LabelButtonClickFramedNoTextWithImageFramedWindowImpl(
    base::WaitableEvent* event) {
  LabelButtonClick(event, true, false, true, true);
}

void LabelButtonClickFramedNoTextNoImageFramedWindowImpl(
    base::WaitableEvent* event) {
  LabelButtonClick(event, true, false, false, true);
}

void LabelButtonClickFramedNoTextWithImageFramelessWindowImpl(
    base::WaitableEvent* event) {
  LabelButtonClick(event, true, false, true, false);
}

void LabelButtonClickFramedNoTextNoImageFramelessWindowImpl(
    base::WaitableEvent* event) {
  LabelButtonClick(event, true, false, false, false);
}

void LabelButtonClickFramelessWithTextWithImageFramedWindowImpl(
    base::WaitableEvent* event) {
  LabelButtonClick(event, false, true, true, true);
}

void LabelButtonClickFramelessWithTextNoImageFramedWindowImpl(
    base::WaitableEvent* event) {
  LabelButtonClick(event, false, true, false, true);
}

void LabelButtonClickFramelessWithTextWithImageFramelessWindowImpl(
    base::WaitableEvent* event) {
  LabelButtonClick(event, false, true, true, false);
}

void LabelButtonClickFramelessWithTextNoImageFramelessWindowImpl(
    base::WaitableEvent* event) {
  LabelButtonClick(event, false, true, false, false);
}

void LabelButtonClickFramelessNoTextWithImageFramedWindowImpl(
    base::WaitableEvent* event) {
  LabelButtonClick(event, false, false, true, true);
}

void LabelButtonClickFramelessNoTextNoImageFramedWindowImpl(
    base::WaitableEvent* event) {
  LabelButtonClick(event, false, false, false, true);
}

void LabelButtonClickFramelessNoTextWithImageFramelessWindowImpl(
    base::WaitableEvent* event) {
  LabelButtonClick(event, false, false, true, false);
}

void LabelButtonClickFramelessNoTextNoImageFramelessWindowImpl(
    base::WaitableEvent* event) {
  LabelButtonClick(event, false, false, false, false);
}

}  // namespace

// Test LabelButton functionality. This is primarily to exercise exposed CEF
// APIs and is not intended to comprehensively test button-related behavior
// (which we presume that Chromium is testing).
BUTTON_TEST_ASYNC(LabelButtonClickFramedWithTextWithImageFramedWindow);
BUTTON_TEST_ASYNC(LabelButtonClickFramedWithTextNoImageFramedWindow);
BUTTON_TEST_ASYNC(LabelButtonClickFramedWithTextWithImageFramelessWindow);
BUTTON_TEST_ASYNC(LabelButtonClickFramedWithTextNoImageFramelessWindow);
BUTTON_TEST_ASYNC(LabelButtonClickFramedNoTextWithImageFramedWindow);
BUTTON_TEST_ASYNC(LabelButtonClickFramedNoTextNoImageFramedWindow);
BUTTON_TEST_ASYNC(LabelButtonClickFramedNoTextWithImageFramelessWindow);
BUTTON_TEST_ASYNC(LabelButtonClickFramedNoTextNoImageFramelessWindow);
BUTTON_TEST_ASYNC(LabelButtonClickFramelessWithTextWithImageFramedWindow);
BUTTON_TEST_ASYNC(LabelButtonClickFramelessWithTextNoImageFramedWindow);
BUTTON_TEST_ASYNC(LabelButtonClickFramelessWithTextWithImageFramelessWindow);
BUTTON_TEST_ASYNC(LabelButtonClickFramelessWithTextNoImageFramelessWindow);
BUTTON_TEST_ASYNC(LabelButtonClickFramelessNoTextWithImageFramedWindow);
BUTTON_TEST_ASYNC(LabelButtonClickFramelessNoTextNoImageFramedWindow);
BUTTON_TEST_ASYNC(LabelButtonClickFramelessNoTextWithImageFramelessWindow);
BUTTON_TEST_ASYNC(LabelButtonClickFramelessNoTextNoImageFramelessWindow);


namespace {

const int kMenuItemID = 2;
const char kMenuItemLabel[] = "My Menu Item";

void ClickMenuItem(CefRefPtr<CefMenuButton> menu_button) {
  // Determine the lower-right corner of the menu button, then offset a bit to
  // hit the first menu item.
  const CefRect& bounds = menu_button->GetBoundsInScreen();
  const CefPoint& click_point = CefPoint(bounds.x + bounds.width + 10,
                                         bounds.y + bounds.height + 10);

  // Click the menu item.
  CefRefPtr<CefWindow> window = menu_button->GetWindow();
  window->SendMouseMove(click_point.x, click_point.y);
  window->SendMouseEvents(MBT_LEFT, true, true);
}

class TestMenuButtonDelegate : public CefMenuButtonDelegate,
                               public CefMenuModelDelegate {
 public:
  TestMenuButtonDelegate() {
  }

  void OnMenuButtonPressed(CefRefPtr<CefMenuButton> menu_button,
                           const CefPoint& screen_point) override {
    window_ = menu_button->GetWindow();

    CefRefPtr<CefMenuModel> model = CefMenuModel::CreateMenuModel(this);
    model->AddItem(kMenuItemID, kMenuItemLabel);

    // Wait a bit before trying to click the menu item.
    CefPostDelayedTask(TID_UI, base::Bind(ClickMenuItem, menu_button),
                       kClickDelayMS);

    menu_button->ShowMenu(model, screen_point, CEF_MENU_ANCHOR_TOPLEFT);
  }

  void OnButtonPressed(CefRefPtr<CefButton> button) override {
  }

  void ExecuteCommand(CefRefPtr<CefMenuModel> menu_model,
                      int command_id,
                      cef_event_flags_t event_flags) override {
    EXPECT_TRUE(menu_model.get());
    EXPECT_EQ(command_id, kMenuItemID);

    // Complete the test by closing the window.
    window_->GetWindow()->Close();
    window_ = nullptr;
  }

 private:
  CefRefPtr<CefWindow> window_;

  IMPLEMENT_REFCOUNTING(TestMenuButtonDelegate);
  DISALLOW_COPY_AND_ASSIGN(TestMenuButtonDelegate);
};

void RunMenuButtonClick(bool with_frame,
                        bool with_text,
                        bool with_menu_marker,
                        bool with_image,
                        CefRefPtr<CefWindow> window) {
  CefRefPtr<CefMenuButton> button = CefMenuButton::CreateMenuButton(
      new TestMenuButtonDelegate(), with_text ? kButtonText : "", with_frame,
      with_menu_marker);
  button->SetID(kButtonID);

  EXPECT_TRUE(button->AsButton());
  EXPECT_TRUE(button->AsButton()->AsLabelButton());
  EXPECT_TRUE(button->AsButton()->AsLabelButton()->AsMenuButton());
  EXPECT_EQ(kButtonID, button->GetID());
  EXPECT_TRUE(button->IsVisible());
  EXPECT_FALSE(button->IsDrawn());

  if (with_text)
    EXPECT_STREQ(kButtonText, button->GetText().ToString().c_str());
  else
    EXPECT_TRUE(button->GetText().empty());
 
  if (with_image)
    AddImage(button);

  window->AddChildView(button);
  window->Layout();

  EXPECT_TRUE(window->IsSame(button->GetWindow()));
  EXPECT_TRUE(window->IsSame(button->GetParentView()));
  EXPECT_TRUE(button->IsSame(window->GetViewForID(kButtonID)));
  EXPECT_TRUE(button->IsVisible());
  EXPECT_TRUE(button->IsDrawn());

  window->Show();

  // Wait a bit before trying to click the button.
  CefPostDelayedTask(TID_UI, base::Bind(ClickButton, window, kButtonID),
                     kClickDelayMS);
}

void MenuButtonClick(base::WaitableEvent* event,
                     bool with_button_frame,
                     bool with_button_text,
                     bool with_button_menu_marker,
                     bool with_button_image,
                     bool with_window_frame) {
  TestWindowDelegate::RunTest(event,
      base::Bind(RunMenuButtonClick, with_button_frame, with_button_text,
                 with_button_menu_marker, with_button_image),
      !with_window_frame, false);
}

void MenuButtonClickFramedWithTextWithMarkerWithImageFramedWindowImpl(
    base::WaitableEvent* event) {
  MenuButtonClick(event, true, true, true, true, true);
}

void MenuButtonClickFramedWithTextNoMarkerWithImageFramedWindowImpl(
    base::WaitableEvent* event) {
  MenuButtonClick(event, true, true, false, true, true);
}

void MenuButtonClickFramedWithTextWithMarkerNoImageFramedWindowImpl(
    base::WaitableEvent* event) {
  MenuButtonClick(event, true, true, true, false, true);
}

void MenuButtonClickFramedWithTextNoMarkerNoImageFramedWindowImpl(
    base::WaitableEvent* event) {
  MenuButtonClick(event, true, true, false, false, true);
}

void MenuButtonClickFramedWithTextWithMarkerWithImageFramelessWindowImpl(
    base::WaitableEvent* event) {
  MenuButtonClick(event, true, true, true, true, false);
}

void MenuButtonClickFramedWithTextNoMarkerWithImageFramelessWindowImpl(
    base::WaitableEvent* event) {
  MenuButtonClick(event, true, true, false, true, false);
}

void MenuButtonClickFramedWithTextWithMarkerNoImageFramelessWindowImpl(
    base::WaitableEvent* event) {
  MenuButtonClick(event, true, true, true, false, false);
}

void MenuButtonClickFramedWithTextNoMarkerNoImageFramelessWindowImpl(
    base::WaitableEvent* event) {
  MenuButtonClick(event, true, true, false, false, false);
}

void MenuButtonClickFramedNoTextWithMarkerWithImageFramedWindowImpl(
    base::WaitableEvent* event) {
  MenuButtonClick(event, true, false, true, true, true);
}

void MenuButtonClickFramedNoTextNoMarkerWithImageFramedWindowImpl(
    base::WaitableEvent* event) {
  MenuButtonClick(event, true, false, false, true, true);
}

void MenuButtonClickFramedNoTextWithMarkerNoImageFramedWindowImpl(
    base::WaitableEvent* event) {
  MenuButtonClick(event, true, false, true, false, true);
}

void MenuButtonClickFramedNoTextNoMarkerNoImageFramedWindowImpl(
    base::WaitableEvent* event) {
  MenuButtonClick(event, true, false, false, false, true);
}

void MenuButtonClickFramedNoTextWithMarkerWithImageFramelessWindowImpl(
    base::WaitableEvent* event) {
  MenuButtonClick(event, true, false, true, true, false);
}

void MenuButtonClickFramedNoTextNoMarkerWithImageFramelessWindowImpl(
    base::WaitableEvent* event) {
  MenuButtonClick(event, true, false, false, true, false);
}

void MenuButtonClickFramedNoTextWithMarkerNoImageFramelessWindowImpl(
    base::WaitableEvent* event) {
  MenuButtonClick(event, true, false, true, false, false);
}

void MenuButtonClickFramedNoTextNoMarkerNoImageFramelessWindowImpl(
    base::WaitableEvent* event) {
  MenuButtonClick(event, true, false, false, false, false);
}

void MenuButtonClickFramelessWithTextWithMarkerWithImageFramedWindowImpl(
    base::WaitableEvent* event) {
  MenuButtonClick(event, false, true, true, true, true);
}

void MenuButtonClickFramelessWithTextNoMarkerWithImageFramedWindowImpl(
    base::WaitableEvent* event) {
  MenuButtonClick(event, false, true, false, true, true);
}

void MenuButtonClickFramelessWithTextWithMarkerNoImageFramedWindowImpl(
    base::WaitableEvent* event) {
  MenuButtonClick(event, false, true, true, false, true);
}

void MenuButtonClickFramelessWithTextNoMarkerNoImageFramedWindowImpl(
    base::WaitableEvent* event) {
  MenuButtonClick(event, false, true, false, false, true);
}

void MenuButtonClickFramelessWithTextWithMarkerWithImageFramelessWindowImpl(
    base::WaitableEvent* event) {
  MenuButtonClick(event, false, true, true, true, false);
}

void MenuButtonClickFramelessWithTextNoMarkerWithImageFramelessWindowImpl(
    base::WaitableEvent* event) {
  MenuButtonClick(event, false, true, false, true, false);
}

void MenuButtonClickFramelessWithTextWithMarkerNoImageFramelessWindowImpl(
    base::WaitableEvent* event) {
  MenuButtonClick(event, false, true, true, false, false);
}

void MenuButtonClickFramelessWithTextNoMarkerNoImageFramelessWindowImpl(
    base::WaitableEvent* event) {
  MenuButtonClick(event, false, true, false, false, false);
}

void MenuButtonClickFramelessNoTextWithMarkerWithImageFramedWindowImpl(
    base::WaitableEvent* event) {
  MenuButtonClick(event, false, false, true, true, true);
}

void MenuButtonClickFramelessNoTextNoMarkerWithImageFramedWindowImpl(
    base::WaitableEvent* event) {
  MenuButtonClick(event, false, false, false, true, true);
}

void MenuButtonClickFramelessNoTextWithMarkerNoImageFramedWindowImpl(
    base::WaitableEvent* event) {
  MenuButtonClick(event, false, false, true, false, true);
}

void MenuButtonClickFramelessNoTextNoMarkerNoImageFramedWindowImpl(
    base::WaitableEvent* event) {
  MenuButtonClick(event, false, false, false, false, true);
}

void MenuButtonClickFramelessNoTextWithMarkerWithImageFramelessWindowImpl(
    base::WaitableEvent* event) {
  MenuButtonClick(event, false, false, true, true, false);
}

void MenuButtonClickFramelessNoTextNoMarkerWithImageFramelessWindowImpl(
    base::WaitableEvent* event) {
  MenuButtonClick(event, false, false, false, true, false);
}

void MenuButtonClickFramelessNoTextWithMarkerNoImageFramelessWindowImpl(
    base::WaitableEvent* event) {
  MenuButtonClick(event, false, false, true, false, false);
}

void MenuButtonClickFramelessNoTextNoMarkerNoImageFramelessWindowImpl(
    base::WaitableEvent* event) {
  MenuButtonClick(event, false, false, false, false, false);
}

}  // namespace

// Test MenuButton functionality. This is primarily to exercise exposed CEF
// APIs and is not intended to comprehensively test button-related behavior
// (which we presume that Chromium is testing).
BUTTON_TEST_ASYNC(MenuButtonClickFramedWithTextNoMarkerWithImageFramedWindow);
BUTTON_TEST_ASYNC(MenuButtonClickFramedWithTextWithMarkerWithImageFramedWindow);
BUTTON_TEST_ASYNC(MenuButtonClickFramedWithTextNoMarkerNoImageFramedWindow);
BUTTON_TEST_ASYNC(MenuButtonClickFramedWithTextWithMarkerNoImageFramedWindow);
BUTTON_TEST_ASYNC(
    MenuButtonClickFramedWithTextNoMarkerWithImageFramelessWindow);
BUTTON_TEST_ASYNC(
    MenuButtonClickFramedWithTextWithMarkerWithImageFramelessWindow);
BUTTON_TEST_ASYNC(MenuButtonClickFramedWithTextNoMarkerNoImageFramelessWindow);
BUTTON_TEST_ASYNC(
    MenuButtonClickFramedWithTextWithMarkerNoImageFramelessWindow);
BUTTON_TEST_ASYNC(MenuButtonClickFramedNoTextNoMarkerWithImageFramedWindow);
BUTTON_TEST_ASYNC(MenuButtonClickFramedNoTextWithMarkerWithImageFramedWindow);
BUTTON_TEST_ASYNC(MenuButtonClickFramedNoTextNoMarkerNoImageFramedWindow);
BUTTON_TEST_ASYNC(MenuButtonClickFramedNoTextWithMarkerNoImageFramedWindow);
BUTTON_TEST_ASYNC(MenuButtonClickFramedNoTextNoMarkerWithImageFramelessWindow);
BUTTON_TEST_ASYNC(
    MenuButtonClickFramedNoTextWithMarkerWithImageFramelessWindow);
BUTTON_TEST_ASYNC(MenuButtonClickFramedNoTextNoMarkerNoImageFramelessWindow);
BUTTON_TEST_ASYNC(MenuButtonClickFramedNoTextWithMarkerNoImageFramelessWindow);
BUTTON_TEST_ASYNC(
    MenuButtonClickFramelessWithTextNoMarkerWithImageFramedWindow);
BUTTON_TEST_ASYNC(
    MenuButtonClickFramelessWithTextWithMarkerWithImageFramedWindow);
BUTTON_TEST_ASYNC(MenuButtonClickFramelessWithTextNoMarkerNoImageFramedWindow);
BUTTON_TEST_ASYNC(
    MenuButtonClickFramelessWithTextWithMarkerNoImageFramedWindow);
BUTTON_TEST_ASYNC(
    MenuButtonClickFramelessWithTextNoMarkerWithImageFramelessWindow);
BUTTON_TEST_ASYNC(
    MenuButtonClickFramelessWithTextWithMarkerWithImageFramelessWindow);
BUTTON_TEST_ASYNC(
    MenuButtonClickFramelessWithTextNoMarkerNoImageFramelessWindow);
BUTTON_TEST_ASYNC(
    MenuButtonClickFramelessWithTextWithMarkerNoImageFramelessWindow);
BUTTON_TEST_ASYNC(MenuButtonClickFramelessNoTextNoMarkerWithImageFramedWindow);
BUTTON_TEST_ASYNC(
    MenuButtonClickFramelessNoTextWithMarkerWithImageFramedWindow);
BUTTON_TEST_ASYNC(MenuButtonClickFramelessNoTextNoMarkerNoImageFramedWindow);
BUTTON_TEST_ASYNC(MenuButtonClickFramelessNoTextWithMarkerNoImageFramedWindow);
BUTTON_TEST_ASYNC(
    MenuButtonClickFramelessNoTextNoMarkerWithImageFramelessWindow);
BUTTON_TEST_ASYNC(
    MenuButtonClickFramelessNoTextWithMarkerWithImageFramelessWindow);
BUTTON_TEST_ASYNC(MenuButtonClickFramelessNoTextNoMarkerNoImageFramelessWindow);
BUTTON_TEST_ASYNC(
    MenuButtonClickFramelessNoTextWithMarkerNoImageFramelessWindow);
