#pragma once
#include "../System/ReferencedObject.h"
#include "hhMessage.h"

namespace app::fnd
{
	class CActor;

	// this class doesn't exist in the PC version at all and i don't know what to do with this
	class CActorTraverser : public ReferencedObject
	{
	public:
		virtual bool Callback(CActor& actor) = 0;
	};

	class CActor
	{
	protected:
		unsigned int actorID{};
		void* messageManager{};
		void* unk1{};
		unsigned short flags{ 0 };
		char updateFlags{ 1 };
		bool enabled{ true };
		unsigned int allowedMessageMask{ static_cast<unsigned>(-1) };
		void* unk2{};

	public:
		virtual ~CActor() = default;
		virtual void ForEach(CActorTraverser& traverser) = 0;

		virtual bool PreProcessMessage(Message& msg)
		{
			return false;
		}

		virtual bool ProcessMessage(Message& msg)
		{
			return PreProcessMessage(msg);
		}

		virtual void Update(const SUpdateInfo& info)
		{

		}

		virtual bool ActorProc(int id, void* data) = 0;
	};
}
