//
// Created by dujiajun on 3/3/17.
//

#include "detector/fast_rcnn_detector.hpp"
#include "fusion/detector_only_fusion.hpp"
#include "real_time_monitor.hpp"

int main(){
    // VOC 1+20 classes
    vector<Target::TARGET_CLASS> voc_itc = {
            Target::UNKNOWN,
//            Target::UNKNOWN, Target::BICYCLE, Target::UNKNOWN, Target::UNKNOWN,
            Target::UNKNOWN, Target::UNKNOWN, Target::UNKNOWN, Target::UNKNOWN, //bicycle is easy to confuse with person
            Target::UNKNOWN, Target::BUS, Target::CAR, Target::UNKNOWN,
            Target::UNKNOWN, Target::UNKNOWN, Target::UNKNOWN, Target::UNKNOWN,
            Target::UNKNOWN, Target::MOTORBIKE, Target::PERSON, Target::UNKNOWN,
            Target::UNKNOWN, Target::UNKNOWN, Target::TRAIN, Target::UNKNOWN
    };

    string address="/home/dujiajun/CUHKSquare.mpg";
    string fast_prototxt = "/home/dujiajun/fast-rcnn/models/VGG16/test.prototxt";
    string fast_trained_model = "/home/dujiajun/fast-rcnn/data/fast_rcnn_models/vgg16_fast_rcnn_iter_40000.caffemodel";
//    string faster_prototxt = "/home/dujiajun/py-faster-rcnn/models/pascal_voc/VGG16/faster_rcnn_end2end/test.prototxt";
//    string faster_trained_model = "/home/dujiajun/py-faster-rcnn/data/faster_rcnn_models/VGG16_faster_rcnn_final.caffemodel";
//    FasterRcnnDetector fasterRcnnDetector(faster_prototxt, faster_trained_model);
//    FastRcnnDetector detector(fasterRcnnDetector, fast_prototxt, fast_trained_model);
    FastRcnnDetector detector(fast_prototxt, fast_trained_model, voc_itc);
    DetectorOnlyFusion fusion(detector);
    Displayer displayer;
    RealTimeMonitor monitor(address, fusion, displayer);
    monitor.run();
    while(monitor.isRunning()){
        this_thread::sleep_for(chrono::milliseconds(100));
    }
}
