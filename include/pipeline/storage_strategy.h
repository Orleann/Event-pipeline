//
// Created by Sebastian Sobczyński on 25/11/2026.
//

#pragma once

class IStorageStrategy {
public:
    virtual ~IStorageStrategy() = 0;
    virtual void write(pipeline::Event& event) = 0;
};

