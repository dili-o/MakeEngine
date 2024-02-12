#pragma once

#include <string>

#include "MakeEngine/Core.h"

namespace MK {

	class Texture
	{
	public:
		virtual ~Texture() = default;

		virtual uint32_t GetWidth() const = 0;
		virtual uint32_t GetHeight() const = 0;
		inline virtual uint32_t GetSlot() const = 0;
		virtual void Bind(uint32_t slot = 0) = 0;
	protected:
		uint32_t m_Slot;
	};

	class Texture2D : public Texture
	{
	public:
		static Ref<Texture2D> Create(const std::string& path);
	};

}