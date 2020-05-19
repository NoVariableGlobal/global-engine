#include "Component.h"

class SpecialFloatHandlerComponent : public Component {
  public:
    virtual void updateFloat(float value) = 0;
    void destroy() override;
};
