#pragma once
#include <iostream>
#include <functional>
#include <array>
namespace PandaEngine {

	enum class EventType
	{
		WINDOW_RESIZE = 0,
		WINDOW_CLOSE,

		KEY_PRESSED,
		KEY_RELASED,

		MOUSE_BUTTON_PRESSED,
		MOUSE_BUTTON_RELEASED,
		MOUSE_MOVED,

		EVENTS_COUNT
	};

	struct BaseEvent
	{
		virtual ~BaseEvent() = default;
		virtual EventType GetType() const = 0;
	};

	class EventDispatcher
	{
	public:
		template<typename EventType>
		void AddEventListener(std::function<void(EventType&)> callback)
		{
			auto baseCallback = [func = std::move(callback)](BaseEvent& e)
				{
					if (e.GetType() == EventType::type)
					{
						func(static_cast<EventType&>(e));
					}
				};
			m_eventCallback[static_cast<size_t>(EventType::type)] = std::move(baseCallback);
		}

		void dispatch(BaseEvent& event)
		{
			auto& callback = m_eventCallback[static_cast<size_t>(event.GetType())];
			if (callback)
			{
				callback(event);
			}
		}

	private:
		std::array<std::function<void(BaseEvent&)>, static_cast<size_t>(EventType::EVENTS_COUNT)> m_eventCallback;
	};

	struct EventMouseMoved : public BaseEvent
	{
		EventMouseMoved(const double x, const double y)
			: x(x)
			, y(y)
		{
		}

		virtual EventType GetType() const override
		{
			return type;
		}

		double x;
		double y;

		static const EventType type = EventType::MOUSE_MOVED;
	};

	struct EventWindowResize : public BaseEvent
	{
		EventWindowResize(const unsigned int width, const unsigned int height)
			: width(width)
			, height(height)
		{
		}

		virtual EventType GetType() const override
		{
			return type;
		}

		unsigned int width;
		unsigned int height;

		static const EventType type = EventType::WINDOW_RESIZE;
	};

	struct EventWindowClose : public BaseEvent
	{
		virtual EventType GetType() const override
		{
			return type;
		}

		static const EventType type = EventType::WINDOW_CLOSE;
	};

}