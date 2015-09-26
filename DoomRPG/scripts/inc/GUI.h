#ifndef _GUI_DH_
#define _GUI_DH_

NamedScript void ToggleGUI();

NamedScript void CheckCursor();
NamedScript void CheckGUI();

// Window/Control Handling
void HandleWindow(GUIWindow *);
void HandleLabel(GUILabel *);
void HandleIcon(GUIIcon *);
void HandleButton(GUIButton *);
void HandleBar(GUIBar *);
void HandleList(GUIList *);
void DrawTooltip(GUITooltip *);
void HandleContextMenu(GUIContextMenu *);

// Window/Control Creation
GUIWindow *GUICreateWindow();
void GUIDeleteWindow(GUIWindow *);
GUILabel *GUICreateLabel(GUIWindow *);
GUIIcon *GUICreateIcon(GUIWindow *);
GUIButton *GUICreateButton(GUIWindow *);
GUIBar *GUICreateBar(GUIWindow *);
GUIList *GUICreateList(GUIWindow *);
GUITooltip *GUICreateTooltip();
GUIContextMenu *GUICreateContextMenu();

// Utility
void FocusWindow(GUIWindow *);
bool InTitleBar(GUIWindow *);
bool InRegion(int, int, int, int);
void DrawBorder(int, int, int, int);

#endif
