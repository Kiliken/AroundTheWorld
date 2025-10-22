#include "utils.h"

int main()
{

    // WINDOW
    sf::RenderWindow window(sf::VideoMode({1280, 720}), "Around The World");
    // window.setMouseCursorVisible(false);
    window.setFramerateLimit(60);

    sf::Clock clock;

    float timer = 0;

    float offset = 0;

    Noise noise;

    // Seed with random value
    std::srand(static_cast<unsigned>(std::time(nullptr)));
    int seed = std::rand();
    noise.seed(seed);

    // Define terrain types
    TerrainType waterTerrain(0.2f, 0.4f, {30, 176, 251}, {40, 255, 255});
    TerrainType sandTerrain(0.4f, 0.5f, {215, 192, 158}, {255, 246, 193}, 0.3f);
    TerrainType grassTerrain(0.5f, 0.7f, {2, 166, 155}, {118, 239, 124});
    TerrainType treesTerrain(0.7f, 0.75f, {22, 181, 141}, {10, 145, 113}, -0.5f);
    TerrainType rockTerrain(0.75f, 1.0f, {205, 133, 63}, {120, 72, 36}, 0.1f);

    std::vector<TerrainType> terrainTypes = {
        waterTerrain, sandTerrain, grassTerrain, treesTerrain, rockTerrain};

    const int width = 512;
    const int height = 512;

    auto noiseMap = utils::generateNoiseMap(width, height, noise, 125.0f, 4, 0.5f, 2.0f, 0.0f, 0.0f);

    std::vector<std::vector<std::array<int, 3>>> colorMap(width, std::vector<std::array<int, 3>>(height));

    for (int x = 0; x < width; ++x)
    {
        for (int y = 0; y < height; ++y)
        {
            float noiseValue = noiseMap[x][y];

            for (const auto &terrain : terrainTypes)
            {
                if (noiseValue < terrain.maxHeight)
                {
                    colorMap[x][y] = utils::getTerrainColor(noiseValue, terrain);
                    break;
                }
            }
        }
    }

    std::vector<sf::VertexArray> map(16);
    std::vector<sf::Transform> mapPos(16);

    for (int i = 0; i < map.size(); i++)
    {
        map[i] = sf::VertexArray(sf::PrimitiveType::Points, width * height);
        mapPos[i] = sf::Transform();
        mapPos[i].translate({512.f,200.f});
        for (int y = 0; y < height; ++y)
        {
            for (int x = 0; x < width; ++x)
            {
                int index = y * width + x;
                map[i][index].position = sf::Vector2f(x, y);
                map[i][index].color = sf::Color(colorMap[x][y][0], colorMap[x][y][1], colorMap[x][y][2]);
            }
        }
    }
    mapPos[1].translate({-512,-512});

    // MAIN LOOP
    while (window.isOpen())
    {
        sf::Time dt = clock.restart(); // Time since last frame
        float deltaTime = dt.asSeconds();

        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
            {
                window.close();
            }
        }

        // win lose condition
        /*
        timer += deltaTime;
        if (timer > 0.5f)
        {
            timer = 0;
            offset += 0.1f;
            noiseMap = utils::generateNoiseMap(width, height, noise, 125.0f, 4, 0.5f, 2.0f, offset, offset);

            for (int x = 0; x < width; ++x)
            {
                for (int y = 0; y < height; ++y)
                {
                    float noiseValue = noiseMap[x][y];

                    for (const auto &terrain : terrainTypes)
                    {
                        if (noiseValue < terrain.maxHeight)
                        {
                            colorMap[x][y] = utils::getTerrainColor(noiseValue, terrain);
                            break;
                        }
                    }
                }
            }
            for (int y = 0; y < height; ++y)
            {
                for (int x = 0; x < width; ++x)
                {
                    int index = y * width + x;
                    pixels[index].position = sf::Vector2f(x, y);
                    pixels[index].color = sf::Color(colorMap[x][y][0], colorMap[x][y][1], colorMap[x][y][2]);
                }
            }
        }*/

        // RENDERING
        window.clear();

        for (int i = 0; i < map.size(); i++)
        {
            //mapPos[i].translate({0.01f * (float)i, 0.01f * (float)i});
            window.draw(map[i], mapPos[i]);
        }
        window.display();
    }
}