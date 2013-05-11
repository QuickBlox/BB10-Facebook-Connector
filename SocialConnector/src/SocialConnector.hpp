// Default empty project template
#ifndef SocialConnector_HPP_
#define SocialConnector_HPP_

#include <QObject>

namespace bb { namespace cascades { class Application; }}

/*!
 * @brief Application pane object
 *
 *Use this object to create and init app UI, to create context objects, to register the new meta types etc.
 */
class SocialConnector : public QObject
{
    Q_OBJECT
public:
    SocialConnector(bb::cascades::Application *app);
    virtual ~SocialConnector() {}
};


#endif /* SocialConnector_HPP_ */
