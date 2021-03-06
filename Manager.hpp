#pragma once

#include "Geometry.hpp"

#include <X11/Xlib.h>

#include <map>
#include <vector>

struct Client
{
  Window client;
  Window root;
  Rect preMax;
  bool ign;
  Point absOrigin;
};

struct Monitor
{
  std::string name;
  Rect r;
  Window root;
  Point absOrigin;

  Window gridDraw;
  unsigned gridX;
  unsigned gridY;
};

struct Root
{
  int screen;
  Point absOrigin;
};

struct Drag
{
  Window w = 0;

  int xR, yR;
  int x, y;
  int width, height;

  int btn;
  DIR dirVert;
  DIR dirHorz;
};

class Manager
{
  public:

    Manager(const std::string& display,
            const std::map<int,Point>& screens,
            const std::string& screenshotDir);
    ~Manager();

    bool init();
    void addClient(Window w, bool checkIgn);
    void run();

    void onReq_Map(const XMapRequestEvent& e);
    void onNot_Unmap(const XUnmapEvent& e);
    void onReq_Configure(const XConfigureRequestEvent& e);
    void onNot_Motion(const XButtonEvent& e);
    void onKeyPress(const XKeyEvent& e);
    void onBtnPress(const XButtonEvent& e);
    void onClientMessage(const XClientMessageEvent& e);

    void switchFocus(Window w);
    void handleFocusChange(const XFocusChangeEvent& e, bool in);

    void onKeyGridActive(const XKeyEvent& e);
    void onKeyWinExplorer(const XKeyEvent& e);
    void onKeyTerminal(const XKeyEvent& e);
    void onKeyGrid(const XKeyEvent& e);
    void onKeyMoveMonitor(const XKeyEvent& e);
    void onKeyMoveFocus(const XKeyEvent& e);
    void onKeyMaximize(const XKeyEvent& e);
    void onKeyUnmaximize(const XKeyEvent& e);
    void onKeyClose(const XKeyEvent& e);
    void onKeyLauncher(const XKeyEvent& e);
    void onKeyScreenshot(const XKeyEvent& e);

    void snapGrid(Window w, Rect r);
    void onKeySnapGrid(const XKeyEvent& e);
    void onKeyMoveGridLoc(const XKeyEvent& e);
    void onKeyMoveGridSize(const XKeyEvent& e);

    void drawGrid(Monitor* mon, bool active);
    Window getNextWindowInDir(DIR dir, Window w);

  private:

    const std::string& _argDisp;
    const std::map<int,Point>& _argScreens;
    const std::string& _argScreenshotDir;

    Display* _disp = nullptr;
    std::map<Window, Client> _clients;
    std::map<Window, Root> _roots;
    std::vector<Monitor> _monitors;

    Drag _drag = {};
    uint64_t _lastConfigureSerial = 0;
    uint64_t _lastMapSerial = 0;
    bool _gridActive = false;
    Window _lastFocus = 0;
};
