import tmes;

int main([[maybe_unused]] int argc, [[maybe_unused]] char **argv) 
{
    tmes::info("hello {}", 1);
    tmes::success("hello");
    tmes::warn("hello");
    tmes::error("hello");
    tmes::crit("hello");
    return 0;
}
