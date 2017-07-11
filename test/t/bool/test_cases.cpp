
#include <test.hpp>

namespace TestBoolean {

enum class Test : protozero::pbf_tag_type {
    required_bool_b = 1
};

} // end namespace TestBoolean

TEST_CASE("read bool field using pbf_reader") {

    SECTION("false") {
        const std::string buffer = load_data("bool/data-false");

        protozero::pbf_reader item(buffer);

        REQUIRE(item.next());
        REQUIRE(!item.get_bool());
        REQUIRE(!item.next());
    }

    SECTION("true") {
        const std::string buffer = load_data("bool/data-true");

        protozero::pbf_reader item(buffer);

        REQUIRE(item.next());
        REQUIRE(item.get_bool());
        REQUIRE(!item.next());
    }

    SECTION("also true") {
        const std::string buffer = load_data("bool/data-also-true");

        protozero::pbf_reader item(buffer);

        REQUIRE(item.next(1));
        REQUIRE(item.get_bool());
        REQUIRE(!item.next());
    }

    SECTION("still true") {
        const std::string buffer = load_data("bool/data-still-true");

        protozero::pbf_reader item(buffer);

        REQUIRE(item.next(1));
        REQUIRE(item.get_bool());
        REQUIRE(!item.next());
    }

}

TEST_CASE("read bool field using pbf_message") {

    SECTION("false") {
        const std::string buffer = load_data("bool/data-false");

        protozero::pbf_message<TestBoolean::Test> item(buffer);

        REQUIRE(item.next());
        REQUIRE(!item.get_bool());
        REQUIRE(!item.next());
    }

    SECTION("true") {
        const std::string buffer = load_data("bool/data-true");

        protozero::pbf_message<TestBoolean::Test> item(buffer);

        REQUIRE(item.next());
        REQUIRE(item.get_bool());
        REQUIRE(!item.next());
    }

    SECTION("also true") {
        const std::string buffer = load_data("bool/data-also-true");

        protozero::pbf_message<TestBoolean::Test> item(buffer);

        REQUIRE(item.next(TestBoolean::Test::required_bool_b));
        REQUIRE(item.get_bool());
        REQUIRE(!item.next());
    }

    SECTION("still true") {
        const std::string buffer = load_data("bool/data-still-true");

        protozero::pbf_message<TestBoolean::Test> item(buffer);

        REQUIRE(item.next(TestBoolean::Test::required_bool_b));
        REQUIRE(item.get_bool());
        REQUIRE(!item.next());
    }

}

TEST_CASE("write bool field using pbf_writer") {

    std::string buffer;
    protozero::pbf_writer pw(buffer);

    SECTION("false") {
        pw.add_bool(1, false);
        REQUIRE(buffer == load_data("bool/data-false"));
    }

    SECTION("true") {
        pw.add_bool(1, true);
        REQUIRE(buffer == load_data("bool/data-true"));
    }

}

TEST_CASE("write bool field using pbf_builder") {

    std::string buffer;
    protozero::pbf_builder<TestBoolean::Test> pw(buffer);

    SECTION("false") {
        pw.add_bool(TestBoolean::Test::required_bool_b, false);
        REQUIRE(buffer == load_data("bool/data-false"));
    }

    SECTION("true") {
        pw.add_bool(TestBoolean::Test::required_bool_b, true);
        REQUIRE(buffer == load_data("bool/data-true"));
    }

}

TEST_CASE("write bool field using moved pbf_builder") {

    std::string buffer;
    protozero::pbf_builder<TestBoolean::Test> pw2{buffer};
    REQUIRE(pw2.valid());

    protozero::pbf_builder<TestBoolean::Test> pw{std::move(pw2)};
    REQUIRE(pw.valid());
    REQUIRE_FALSE(pw2.valid());

    SECTION("false") {
        pw.add_bool(TestBoolean::Test::required_bool_b, false);
        REQUIRE(buffer == load_data("bool/data-false"));
    }

    SECTION("true") {
        pw.add_bool(TestBoolean::Test::required_bool_b, true);
        REQUIRE(buffer == load_data("bool/data-true"));
    }

}

