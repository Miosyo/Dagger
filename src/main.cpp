#include <Dagger\Game.hpp>

int main(int argc, char** argv)
{
	if(Dagger::Init())
		Dagger::Run();
	return EXIT_SUCCESS;
}