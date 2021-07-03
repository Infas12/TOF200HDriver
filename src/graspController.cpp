#include "graspController.h"
//
// Created by tiger on 2021/7/2.
//

void graspController::update()
{
    sendCommand();
    updateFeedback();
}

void graspController::sendCommand() {
    //TODO: send BYTES. Try to use packet this time...

}

void graspController::updateFeedback()
{
    int size = m_p_serialPort ->available();
    std::vector<std::string> feedbackMessageList = m_p_serialPort -> readlines(size,"\n");//read all the lines received.

    if(!feedbackMessageList.empty()) {
        for (auto iter = feedbackMessageList.begin(); iter != feedbackMessageList.end(); iter++) {
            try{
                std::string ID = iter->substr(1,3);
                std::string ECD = iter->substr(5,4);
                int tmp_ID = std::stoi(ID);
                float tmp_Angle = std::stof(ECD);
                baseAngleFeedback[tmp_ID] = tmp_Angle;
            }catch(std::exception e){

                break;
            }
        }
    }

}