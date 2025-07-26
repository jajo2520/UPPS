#include "Grid.h"
#include "Particle.h"
#include "Constants.h"
#include "ParticleQueue.h"

using size_t = std::size_t;

Grid::Grid() : mData(screen::ROW_NUM * screen::COL_NUM),
                                      rows {screen::ROW_NUM},
                                      cols {screen::COL_NUM}
{}

size_t Grid::getIndex(size_t row, size_t col)
{
    return row*screen::ROW_NUM + col;
}

void Grid::addParticle(Particle* particle, size_t row, size_t col)
{
    size_t pos {getIndex(row, col)};
    mData[pos].push_back(particle);
}

void Grid::removeParticle(Particle* particle, size_t row, size_t col)
{

    size_t pos {getIndex(row, col)};
    for (size_t i {}; i < mData[pos].size(); ++i)
    {
        if (mData[pos][i] == particle)
        {
            // remove pointer to object from vec
            mData[pos].erase(mData[pos].begin() + i);
            break;
        }
    }
}

std::vector<Particle*>& Grid::getParticles(size_t row, size_t col)
{
    size_t pos {getIndex(row, col)};
    return mData[pos];
}

void Grid::eraseGrid()
{
    for (auto& loc : mData)
    {
        for (size_t i {}; i < loc.size(); ++i)
        {
            loc.erase(loc.begin());
        }
    }
}

