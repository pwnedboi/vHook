class ccombobox {
public:
    /* this class only handles all the open checks for the combo boxes, nothing more. */
    bool esp_opend;
    bool hitbox_opend;
    bool aaY_opend;
    bool aaX_opend;
    bool hands_opend;
    bool players_opend;
    bool playerlist_opend_x[64];
    bool playerlist_opend_y[64];
	bool clan_opend;
	bool colors_opend;
	bool crossT_opend;
	bool crossC_opend;
	bool weapon_opend;
	bool viscol_opend;
	bool aim_opend;
    bool walk_opend;
	
	bool mCol_opend;
	bool cfg_opend;
	
	
	// Skin changer
	bool team_opend;
	bool guns_opend, pistols_opend, heavy_opend, smgs_opend, rifles_opend, knives_opend;
	bool rskins_opend, kskins_opend, pskins_opend, sskins_opend, hskins_opened;
	
    bool misc_clantag, misc_name, misc_changename;
    int inputIndex = 0;
};

/* Change values for settings to be active on startup */
class cVariables : public ccombobox {
public:
    bool menu = false;
    bool newmenu = false;
    int buttonPadding = 24;
    int tabIndex;
    int menueffect = 0;
    bool cfgInit = false;
    
    class cAimbot {
    public:
        bool enabled	= false;
        bool silent		= false;
        bool psilent	= false;
		bool smooth		= false;
		bool rcs		= false;
        bool spiral     = false;
		float smoothf	= .5;
		int rcsf        = 25;
        float spiralx   = 1.f;
        float spiraly   = 1.f;
        int fov			= 1;
		int hitbox		= 7;
        int pointscale	= 73;
        int bone		= 6;
        bool hitscan	= false;
        bool selfpred	= false;
        bool autowall	= false;
        bool autoshoot	= false;
        bool autopistol = false;
        bool autocrouch = false;
        bool autostop	= false;
		bool trigger	= false;
		bool prediciton = false;
		bool enginepred	= false;
		int selected;
        ButtonCode_t triggerKey  = MOUSE_4;
    }aimbot;
    
    class cVisuals {
    public:
        bool enabled	= false;
        bool box		= false;
        bool box3d      = false;
        bool name		= false;
        bool health		= false;
        bool healthtext = false;
        bool active		= false;
        bool snapline	= false;
        bool handchams	= false;
		bool weaponchams= false;
		bool weapons	= false;
        bool skeleton	= false;
        bool chams		= false;
        bool headhitbox = false;
        bool enemyonly	= false;
    
		bool bombtimer	= false;
        
        bool grenade    = false;
		
		bool crosshair	= false;
        
        int handsType	= 4; // 0 - lit, 1 - texture, 2 - wireframe, 3 - nohands, 4 - multi
        int playersType = 1;
		int weaponType	= 1;
        
        int handchams_alpha		= 255;
        int playerchams_alpha	= 255;
		int weapons_alpha		= 255;
        
        int coltab;
        
        int tchams[4]			= { 255, 255, 0, 255 };
        int ctchams[4]			= { 0, 255, 0, 255 };
        
        int tchams_ignore[4]	= { 236, 81, 63, 255 };
        int ctchams_ignore[4]	= { 51, 124, 197, 255 }; // this color is soo fucking p100!
        
        int tbox[4]				= { 255, 255, 0, 255 };
        int ctbox[4]			= { 0, 255, 0, 255 };
        
        int tbox_ignore[4]		= { 236, 81, 63, 255 };
        int ctbox_ignore[4]		= { 51, 124, 197, 255 }; // this color is soo fucking p100!
        
    }visuals;
    
    class cMisc {
    public:
        bool enabled		= true;
        
        bool norecoil		= false;
        bool novisualrecoil = false;
        
		bool bhop			= true;
        bool autostrafe		= true;
        bool circlestrafe	= false;
        
        bool fov			= false;
        int fovf			= 1;
        
        bool airstuck		= false;
        bool showrank		= true;
        bool skinchanger	= false;
		bool noscope		= false;
        bool asuswalls      = false;
        
		int fakelagfactor	= 1;
		bool fakelag		= false;
		bool adaptive		= false;
        
		bool noflash		= true;
		float flashalpha	= 160.f;
        
		bool spammer		= false;
		bool clantag		= false;
        
		int crosshairType	= 0;
        
		bool nosky			= false;
		bool worldpaint		= false;
		bool antiscreenshot = true;
		bool antiuntrust	= true;
        
        ButtonCode_t airstuckKey     = KEY_Z;
        ButtonCode_t cStrafeKey      = KEY_PERIOD;
		// Anti Aim
		bool thirdpersonmode= false;
		bool anitaim		= false;
        bool antiresolve    = false;
        int aaY				= 0;
        int aaX				= 0;
        bool attargets		= false;
        int customaa		= 0;
        int fakeyaw			= 180;
        int realyaw			= 20;
		bool fakeaa			= false;
    }misc;
    
    class cColors {
    public:
		bool enabled = false;
        int tab = 0;
		int cColor = 4;
		int combo = 0;
		
        Color ctchams;
        Color tchams;
        
        Color ctchams_ign;
        Color tchams_ign;
        
        Color tbox;
        Color tbox_ign;
        
        Color ctbox;
        Color ctbox_ign;
        
        Color hands;
        Color hands_ign;
		
		Color weapons;
		Color weapons_ign;
		
		Color dropped;
		Color dropped_ign;
        
        Color world;
		Color crosshair;
        
        Color dlights = Color::Blue();
        Color asus = Color(255, 255, 255, 150);
        
    }colors;
	
	class cSkins {
	public:
		bool update = false;
		int team	= 0;
		int rifle	= 0;
		int pistol	= 0;
		int smg		= 0;
		int heavy	= 0;
		int knifeT	= 4;
		int knifeCT = 3;
		
	}skins;
	
	class cMain {
	public:
		int tab = 0;
	}main;
	
    int playerTab = 0;
	bool canmodify;
	
	
	class cWalk{
	public:
		bool walk       = false;
        int CTroute     = 0;
        int Troute      = 0;
        bool forceReset = false;    // if a Reset is queued up by the User
        bool autobuy    = false;    // autobuy during FreezeTime
        int autobuyAt   = 0;        // autobuy >= this amount of cash
	}walk;
	
};

struct Corrections {
    float x, y;
	bool active;
    bool whitelist;
    bool resolved;
    
    int dropdown_x = 0;
    int dropdown_y = 0;
};

extern Corrections gCorrections[64];

extern cVariables vars;
