#include "systems/debug_system.hpp"
#include "components/transform.hpp"
#include "components/renderable3D.hpp"
#include "components/debug/transform_debug.hpp"
#include "registry.hpp"

namespace nith
{
    void DebugSystem::Render(const f32& deltaTime)
    {
        auto view = Registry.view<Transform, TransformDebug>();
        for (auto [entity, transform] : view.each())
        {
            
            ImGui::Begin("Transform");
            ImGui::PushID((int)entity);

            bool isChanged = false;

            isChanged |= ImGui::InputFloat3("Position", &transform.position[0]);
            isChanged |= ImGui::SliderFloat3("Rotation", &transform.rotation[0], -3.14, 3.14);

            if (isChanged)
            {
                auto renderable3D = Registry.try_get<Renderable3D>(entity);
                if (renderable3D)
                    renderable3D->updateModelMatrix(transform);
            }

            ImGui::NewLine();

            ImGui::PopID();
            ImGui::End();
        }
    }
}