#pragma once

namespace app::xgame
{
	class GlobalAmbCoordinator
	{
	public:
		struct KeyData
		{

		};

		struct Request
		{

		};

		csl::ut::MoveArray<KeyData> Unk1{};
		float Unk2{};
		csl::ut::ObjectMoveArray<Request> Unk3{};
		csl::ut::LinkList<Request> Unk4{};
		csl::ut::LinkList<Request> Unk5{};
		fnd::SoundHandle Handle{};
		float Unk6{ 0.5f };
		int Unk7{};
	};
}