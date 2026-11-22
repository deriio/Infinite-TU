// Settings > "Infinite as VST3/AU" tab (docs/plans/vst-au/README.md 8.11, 3.6): install the plugin
// bundles the app carries into the user's plugin folders. Approved 2026-11-07 (12.4).
#include "app/AppShared.h"
#include "app/ui/design/components/FormParts.h"

namespace app
{
   void DrawDawPluginSection()
   {
      FormParts::Section(T("Install"));
      FormParts::Label(T("Status"));
      ImGui::AlignTextToFramePadding();
      ImGui::TextWrapped("%s", T("Use the official Infinite app to manage its VST3 and AU plugins."));
   }
}
