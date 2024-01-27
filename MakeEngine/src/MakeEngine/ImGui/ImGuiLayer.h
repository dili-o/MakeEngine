#pragma once

#include "MakeEngine/Layer.h"

#include "MakeEngine/Events/ApplicationEvent.h"
#include "MakeEngine/Events/KeyEvent.h"
#include "MakeEngine/Events/MouseEvent.h"

namespace MK {

	class MK_API ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer();

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnImGuiRender() override;

		void Begin();
		void End();
	
	private:
		float m_Time = 0.0f;
	};

}