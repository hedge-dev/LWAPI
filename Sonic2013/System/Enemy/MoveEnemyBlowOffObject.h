#pragma once

namespace app
{
    class EnemyBlowOffObject;

    class MoveEnemyBlowOffObject : public game::MoveController
    {
    private:
        inline static FUNCTION_PTR(void, __thiscall, ms_fpOnEnter, ASLR(0x0072DA70), MoveEnemyBlowOffObject*);
        inline static FUNCTION_PTR(void, __thiscall, ms_fpUpdate, ASLR(0x0072DB30), MoveEnemyBlowOffObject*, const fnd::SUpdateInfo&);
        inline static FUNCTION_PTR(void, __thiscall, ms_fpSetup, ASLR(0x0072D9E0), MoveEnemyBlowOffObject*, CPhysicsWorld*, float, const csl::math::Vector3&);

    public:
        class CallbackHandle
        {
        public:
            typedef void (GameObject::*MemFunc)();

            /*
                Using MSVC, MemFunc gets aligned to 8 bytes causing this class to become 16 bytes in size.
                The Green Hills compiler used for compiling the Wii U version of the game does not force
                such alignment, which causes the class to have a size of 12 bytes. 

                This can be replicated on MSVC by doing the following:
                #pragma pack(4)
                    MemFunc pFunc{};
                #pragma pack()
            */

            GameObject* pObj{};
            MemFunc pFunc{};

            CallbackHandle()
            {

            }

            CallbackHandle(GameObject* in_pObj, MemFunc in_pFunc) : pObj(in_pObj), pFunc(in_pFunc)
            {

            }
        };
        
        EnemySweepMove SweepMove{};
        csl::ut::MoveArray<game::PhysicsSweepOutput> Sweeps{};
        csl::math::Vector3 GravityDirection{};
        csl::math::Vector3 Unk2{};
        CallbackHandle Callback{};
        bool TargetMove{};

        DEFINE_RTTI_PTR(ASLR(0x00FA08D0));

        MoveEnemyBlowOffObject() : game::MoveController(game::MoveControllerType::eMoveControllerType_EnemyBlowOffObject)
        {
            sizeof(CallbackHandle);
        }

        void SetTargetMove(bool in_targetMove)
        {
            TargetMove = in_targetMove;
        }

        void SetCallbackHandle(CallbackHandle in_callback)
        {
            Callback = in_callback;
        }

        void Setup(CPhysicsWorld* in_pWorld, float in_unk, const csl::math::Vector3& in_rVec)
        {
            ms_fpSetup(this, in_pWorld, in_unk, in_rVec);
            /*SweepMove.Setup(in_pWorld, csl::math::Max(in_unk, 1.0f), 0.1f);

            Sweeps.clear();
            Sweeps.change_allocator(GetOwnerMovement()->GetAllocator());

            Unk2 = in_rVec;*/
        }

        const csl::ut::detail::RuntimeTypeInfo* GetRuntimeTypeInfo() const override
        {
            return GetRuntimeTypeInfoStatic();
        }

        void OnEnter() override
        {
            ms_fpOnEnter(this);

            /*GravityDirection = GetOwnerMovement()->GetGameObject()->GetComponent<game::GOCGravity>()->GetGravityDirection();
            
            game::GOCMovement::ContextParam* pContextParam = GetOwnerMovement()->GetContextParam();
            pContextParam->Velocity -= GravityDirection * pContextParam->Velocity.dot(GravityDirection);*/
        }

        void Update(const fnd::SUpdateInfo& in_rUpdateInfo) override
        {
            ms_fpUpdate(this, in_rUpdateInfo);
        }
    };
}