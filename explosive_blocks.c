#include <stubhook.h>

typedef void Level;

typedef struct {

    void *vt;
    float x;
    float y;
    float z;

} Player;

static Level *level;

static void (*Level$$explode)(void *self, void *entity, float x, float y, float z, float radius);

SHHook(bool, SurvivalMode$$continueDestroyBlock,void *self, int x, int y, int z, int c) {
    
    Level$$explode(level,NULL,x, y-2, z, 5.0);
    return _SurvivalMode$$continueDestroyBlock(self,x,y,z,c);
}

SHHook(void *, LocalPlayer$$LocalPlayer, void *self, void *mcpe, Level *newLevel, void *user, int a, bool b) {

level = newLevel;
return _LocalPlayer$$LocalPlayer(self,mcpe,newLevel,user,a,b);

}


SHConstructor {

SHAppVersion("0.7.1.0") {

    SHStub(SHAddr(0xF0E48), Level$$explode);
    SHStub(SHAddr(0x5abc0), LocalPlayer$$LocalPlayer);
    SHStub(SHAddr(0x186B4C), SurvivalMode$$continueDestroyBlock);
    SHApplyHook(SurvivalMode$$continueDestroyBlock);
    SHApplyHook(LocalPlayer$$LocalPlayer);

}

SHOtherVersion {

    return;

}
    
}
