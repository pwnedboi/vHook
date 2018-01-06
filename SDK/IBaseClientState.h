class CBaseClientState {
public:
    void ForceFullUpdate() {
        *(int*)((uintptr_t)this + 0x204) = -1;
    };
};
