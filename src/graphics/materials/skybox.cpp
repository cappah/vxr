// ----------------------------------------------------------------------------------------
// MIT License
// 
// Copyright(c) 2018 V�ctor �vila
// 
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files(the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions :
// 
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.
// ----------------------------------------------------------------------------------------

#include "../../../include/graphics/materials/skybox.h"

#include "../../../include/engine/engine.h"
#include "../../../include/core/assets.h"
#include "../../../include/components/ibl.h"

namespace vxr
{

  namespace mat
  {

    Skybox::Skybox()
    {
      set_name("Skybox/Cubemap");
      set_shaders("skybox.vert", "skybox.frag");

      set_num_textures(1);
      set_uniforms_enabled(true);
      set_uniforms_name("Unlit");

      set_cull(Cull::Front);
      set_depth_write(false);
      set_depth_func(CompareFunc::LessEqual);
    }

    Skybox::Instance::Instance()
    {
      init("Skybox/Cubemap");
      set_color_texture(Engine::ref().assetManager()->default_cubemap());

      uniforms_.unlit.color = vec4(1);
    }

    void Skybox::Instance::onGUI()
    {
      MaterialInstance::onGUI();
      ImGui::Text("Tint       "); ImGui::SameLine();
      ImGui::ColorEdit4(uiText("##Tint").c_str(), (float*)& uniforms_.unlit.color);
      if (ImGui::SmallButton(uiText("Preview Cubemap##LOADtest2").c_str()))
      {
        set_color_texture(Engine::ref().ibl()->main()->cubemap_texture());
      }
      if (ImGui::SmallButton(uiText("Preview Irradiance##LOADtest3").c_str()))
      {
        set_color_texture(Engine::ref().ibl()->main()->irradiance_cubemap_texture());
      }
      if (ImGui::SmallButton(uiText("Preview Prefiltering##LOADtest4").c_str()))
      {
        set_color_texture(Engine::ref().ibl()->main()->prefiltered_cubemap_texture());
      }
    }

    void Skybox::Instance::set_tint(Color color)
    {
      uniforms_.unlit.color = color.rgba();
    }

    Color Skybox::Instance::tint() const
    {
      return Color(uniforms_.unlit.color);
    }

    void Skybox::Instance::set_color_texture(ref_ptr<Texture> texture)
    {
      set_texture(0, texture);
    }

    ref_ptr<Texture> Skybox::Instance::color_texture() const
    {
      return texture(0);
    }

  }

}