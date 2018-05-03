int WifiDisplaySink::dealWithAVFormateTiming(const sp<ParsedMessage> &data){
	const char *content = data->getContent();
	if((mState != PAUSED || mState != PLAYING) && (NULL == strstr(content, "wfd_av_format_change_timing"))) {
		ALOGD("[merlin][Error]:mStat=%d content=%s" , mState, content);
		return -1;
	}
	size_t dataParseLength = 0;
	sp<ParsedMessage> params = ParsedMessage::Parse(content, strlen(content), true, &dataParseLength);
	AString changeTimeFiled;
	if (!(params->findString("wfd_av_format_change_timing", &changeTimeFiled))) {
		ALOGE("[merlin]:Missing av format changing timing field.");
	} else {
		uint64_t ptsFlag = 0, dtsFlag = 0;
		sscanf(changeTimeFiled.c_str(), "%Lx %Lx", &ptsFlag, &dtsFlag);
		ALOGD("[merlin]:ptsFlag %lld dtsFlag %lld", ptsFlag, dtsFlag);
		if(mRTPSink != NULL){
			mRTPSink->avFormatTimeChange(ptsFlag >> 7);
			ALOGD("[merlin]:ptsFlag %lld dtsFlag %lld", ptsFlag, dtsFlag);
		}	
	}
	return 0;
}


