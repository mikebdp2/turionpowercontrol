class Brazos: protected Processor {
private:

	bool getDramValid(DWORD device);
	int getDramFrequency (DWORD device);
	void getDramTimingHigh(DWORD device, DWORD *TrwtWB, DWORD *TrwtTO,
			DWORD *Twrrd, DWORD *Twrwr, DWORD *Trdrd, DWORD *Tref, DWORD *Trfc0,
			DWORD *Trfc1, DWORD *MaxRdLatency);
	void getDramTimingLow(
			DWORD device, // 0 or 1   DCT0 or DCT1
			DWORD *Tcl, DWORD *Trcd, DWORD *Trp, DWORD *Trtp, DWORD *Tras,
			DWORD *Trc, DWORD *Twr, DWORD *Trrd, DWORD *Tcwl, DWORD *T_mode,
			DWORD *Twtr, DWORD *Tfaw);


public:

	Brazos ();

 	static bool isProcessorSupported ();

	void showFamilySpecs ();
	void showHTC();
	void showHTLink();
	void showDramTimings ();

	float convertVIDtoVcore (DWORD);
	DWORD convertVcoretoVID (float);
	DWORD convertFDtoFreq (float);
	void convertFreqtoFD(DWORD, float *);
		
	void setVID (PState , DWORD);
	void setDID (PState , float);

	DWORD getVID (PState);
	float getDID (PState);

	void setFrequency (PState , DWORD);
	void setVCore (PState, float);

	DWORD getFrequency (PState);
	float getVCore (PState);

	void pStateEnable (PState) ;
	void pStateDisable (PState);
	bool pStateEnabled (PState);

	void setMaximumPState (PState);
	PState getMaximumPState ();

	void forcePState (PState);

	DWORD minVID ();
	DWORD maxVID ();

	DWORD startupPState ();
	DWORD maxCPUFrequency ();

	DWORD getTctlRegister (void);
	DWORD getTctlMaxDiff (void);

	DWORD getRampTime (void);
	void setRampTime (DWORD);

	//HTC Section - Read status
	bool HTCisCapable ();
	bool HTCisEnabled ();
	bool HTCisActive ();
	bool HTChasBeenActive ();
	DWORD HTCTempLimit ();
	bool HTCSlewControl ();
	DWORD HTCHystTemp ();
	DWORD HTCPStateLimit ();
	bool HTCLocked ();

	DWORD getAltVID ();

	//HTC Section - Change status
	void HTCEnable ();

	void HTCDisable ();
	void HTCsetTempLimit (DWORD);
	void HTCsetHystLimit (DWORD);
	void setAltVid (DWORD);
		
	//PSI_L bit
	bool getPsiEnabled ();
	DWORD getPsiThreshold ();
	void setPsiEnabled (bool);
	void setPsiThreshold (DWORD);

	//HyperTransport Section

	//Various settings
	bool getC1EStatus ();
	void setC1EStatus (bool);

	// Autocheck mode
	void checkMode ();

	//Performance counters
	void perfCounterGetInfo ();
	void perfCounterGetValue (unsigned int);
	void perfMonitorCPUUsage ();
	void perfMonitorFPUUsage ();
	void perfMonitorDCMA ();

	//Scaler helper methods
	void getCurrentStatus (struct procStatus *pStatus, DWORD core);

};

