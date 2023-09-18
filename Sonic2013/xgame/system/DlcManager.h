#pragma once

namespace app::xgame
{
	typedef ushort DlcType;
	typedef ushort DlcStageIndex;
	
	inline static constexpr ushort ms_DlcIndices[] = { 16, 17, 18 };

	class DlcManagerImpl;

	class DlcManager : public fnd::ReferencedObject, public csl::fnd::SingletonPointer<DlcManager>
	{
	public:
		class SetupInfo
		{
		public:
			ushort DlcIndices[16]{};
			ushort DlcTypes[16]{};
			int DlcCount{};

			void SetContent(ushort in_dlcIndex, ushort in_dlcType)
			{
				DlcIndices[DlcCount] = in_dlcIndex;
				DlcTypes[DlcCount] = in_dlcType;
				DlcCount++;
			}
		};

		DlcManagerImpl* pImpl{};

		DlcManager();
		bool IsPurchase(ushort in_dlcType) const;
		void Update();
	};

	class DlcManagerImpl
	{
	public:
		struct ContentData
		{
			uint Index{};
			ushort DlcType{};
			ushort DlcIndex{};
			bool IsBound{};
			bool IsPurchased{};
		};

		csl::fnd::IAllocator* pAllocator{};
		AocManager* pAocManager{ csl::fnd::Singleton<AocManager>::GetInstance() };
		void* pOpenedTitle{};
		csl::ut::InplaceMoveArray<ContentData, 16> Contents{ nullptr };
		int Unk1{};
		INSERT_PADDING(4) {};

		DlcManagerImpl(csl::fnd::IAllocator* in_pAllocator) : pAllocator(in_pAllocator)
		{

		}

		bool isComplete() const
		{
			return !Unk1 || Unk1 == 4;
		}

		bool isPurchase(ushort in_dlcType) const
		{
			if (Unk1 != 4)
				return false;
		
			if (Contents.empty())
				return false;
		
			for (auto content : Contents)
			{
				if (content.DlcType == in_dlcType)
					return content.IsPurchased;
			}
			
			return false;
		}

		void update()
		{
			switch (Unk1)
			{
			case 0:
				break;
			
			case 1:
			{
				pAocManager->TitleListUpAsync();
				Unk1 = 2;
				break;
			}

			case 2:
			{
				if (!pAocManager->IsTitleEnumerationComplete())
					break;

				Unk1 = 4;

				int titleCount = pAocManager->GetNumTitles();
				if (!titleCount)
					break;

				pOpenedTitle = pAocManager->OpenTitle(0);

				const char* pContentPath = pAocManager->GetContentPath(pOpenedTitle);
				if (!pContentPath)
					pAocManager->CloseTitle(pOpenedTitle);

				auto* pFileSystem = csl::fnd::Singleton<fnd::FileSystem>::GetInstance();

				if (Contents.empty())
				{
					Unk1 = 3;
					break;
				}

				if (pFileSystem->m_LoadFlags.test(0))
				{
					size_t contentCount = Contents.size();

					bool* pIsPurchased = fnd::AllocateTemp<bool>(contentCount);
					ushort* pDlcIndices = fnd::AllocateTemp<ushort>(contentCount);

					for (size_t i = 0; i < contentCount; i++)
						pDlcIndices[i] = Contents[i].DlcIndex;

					pAocManager->GetPurchaseInfo(pOpenedTitle, pIsPurchased, pDlcIndices, contentCount);

					for (size_t i = 0; i < contentCount; i++)
						Contents[i].IsPurchased = pIsPurchased[i];

					fnd::DeallocateTemp(pIsPurchased);
					fnd::DeallocateTemp(pDlcIndices);
				}
				else
				{
					size_t contentCount = Contents.size();
					if (contentCount)
					{
						for (size_t i = 0; i < contentCount; i++)
							Contents[i].IsPurchased = 1;
					}
				}

				if (!Contents.size())
				{
					Unk1 = 3;
					break;
				}

				size_t contentCount = Contents.size();
				for (size_t i = 0; i < contentCount; i++)
				{
					if (pFileSystem->m_LoadFlags.test(0) && Contents[i].DlcType == 1 && Contents[i].IsPurchased)
					{
						char buffer[255]{};
						csl::fnd::Snprintf(buffer, sizeof(buffer), "%s%04x/sonic2013_dlc_%04x.cpk", pContentPath, Contents[i].DlcIndex, Contents[i].DlcIndex);
						Contents[i].Index = pFileSystem->GetDefaultBinder()->BindCpk(buffer, 256, true);
					}
				}

				Unk1 = 3;
				break;
			}

			case 3:
			{
				auto* pFileSystem = csl::fnd::Singleton<fnd::FileSystem>::GetInstance();
				if (!pFileSystem->GetDefaultBinder()->IsSyncCompleteAll())
					break;

				bool dontCloseTitle{};

				size_t contentCount = Contents.size();
				if (contentCount)
				{
					for (size_t i = 0; i < contentCount; i++)
					{
						if (Contents[i].DlcType == 1)
						{
							bool isBound{};

							if (Contents[i].IsPurchased)
							{
								if (pFileSystem->m_LoadFlags.test(0))
									isBound = pFileSystem->GetDefaultBinder()->IsBind(Contents[i].Index);
								else
									Contents[i].IsBound = true;

								Contents[i].IsBound = isBound;
							}

							if (isBound)
								dontCloseTitle = true;
							else
								Contents[i].Index = 0;
						}
						else
						{
							if (Contents[i].DlcType == 2)
								Contents[i].IsBound = Contents[i].IsPurchased;
						}
					}
				}

				if (!dontCloseTitle)
					pAocManager->CloseTitle(pOpenedTitle);
			
				Unk1 = 4;
				break;
			}
			
			default:
				break;
			}
		}
	};

	inline bool IsDLCContentPurchase(DlcType in_type)
	{
		return csl::fnd::Singleton<DlcManager>::GetInstance()->IsPurchase(in_type);
	}

	inline bool IsDLCStagePurchase(DlcStageIndex in_index)
	{
		if (in_index >= 3)
			return false;
	
		return csl::fnd::Singleton<DlcManager>::GetInstance()->IsPurchase(ms_DlcIndices[in_index]);
	}
}

DEFINE_SINGLETONPTR(app::xgame::DlcManager, ASLR(0x00FEFD10));