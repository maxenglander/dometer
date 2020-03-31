#include <memory>

#include "dometer/app/app.hpp"
#include "dometer/event/mock_emitter.hpp"
#include "dometer/metrics/mock_recorder.hpp"
#include "dometer/dns/server/mock_server.hpp"
#include "dometer/util/error.hpp"
#include "gtest/gtest.h"

using ::testing::Return;

namespace dometer::app {
    class AppTest : public ::testing::Test {
        public:
            AppTest()
                : _emitter(std::make_shared<dometer::event::mock_emitter<dometer::dns::event::any_event>>()),
                  _recorder(std::make_shared<dometer::metrics::mock_recorder>()),
                  _server(std::make_shared<dometer::dns::server::mock_server>()),
                  _app(_emitter, _recorder, _server)
            {}
        protected:
            std::shared_ptr<dometer::event::mock_emitter<dometer::dns::event::any_event>> _emitter;
            std::shared_ptr<dometer::metrics::mock_recorder> _recorder;
            std::shared_ptr<dometer::dns::server::mock_server> _server;
            app _app;
    };

    TEST_F(AppTest, WhenStarted_StartsServer) {
        dometer::util::error error{"Server failure", 5};
        EXPECT_CALL(*_server, start("127.0.0.1:6353"))
            .WillOnce(Return(std::x::unexpected<dometer::util::error>(error)));
        auto result = _app.start("127.0.0.1:6353");
        EXPECT_FALSE(result);
        EXPECT_EQ(result.error().message, error.message);
        EXPECT_EQ(result.error().code, error.code);
    }

    TEST_F(AppTest, WhenJoined_JoinsServer) {
        EXPECT_CALL(*_server, join()).Times(1);
        _app.join();
    }

    TEST_F(AppTest, WhenStopped_StopsServer) {
        EXPECT_CALL(*_server, stop()).Times(1);
        _app.stop();
    }

}
