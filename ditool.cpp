#include <iostream>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>

#define STARTSIGNATURE 0x51AB151CABCDEF98
#define MIDSIGNATURE   0x1DD1E51C98765432
#define ENDSIGNATURE   0xEDD51CAE1FDECBA0

#define MAXSUBBLOCKS   1024
#define MAXBLOCKS      (16)// * 1024)

class SubBlockPattern
{
public:
    SubBlockPattern() {}
    void fillSubBLock(uint64_t dir, uint64_t file, uint64_t block, uint64_t subBlockNo, uint64_t offset)
    {
        mStartSignature = STARTSIGNATURE;
        mDirectoryNo    = dir;
        mFileNo         = file;
        mMidSignature   = MIDSIGNATURE;
        mOffset         = offset;
        mBlockNo        = block;
        mSubBlock       = subBlockNo;
        mEndSignature   = ENDSIGNATURE;
    }

    int readVerifySubBLock(uint64_t dir, uint64_t file, uint64_t block, uint64_t subBlockNo, uint64_t offset)
    {
        if ((mStartSignature != STARTSIGNATURE) ||
            (mDirectoryNo    != dir) ||
            (mFileNo         != file) ||
            (mMidSignature   != MIDSIGNATURE) ||
            (mOffset         != offset) ||
            (mBlockNo        != block) ||
            (mSubBlock       != subBlockNo) ||
            (mEndSignature   != ENDSIGNATURE))
        {
            std::cout << "Wrong data in file" << std::endl;
            return -1;
        }

        return 0;
    }


private:
    uint64_t mStartSignature;
    uint64_t mDirectoryNo;
    uint64_t mFileNo;
    uint64_t mMidSignature;
    uint64_t mOffset;
    uint64_t mBlockNo;
    uint64_t mSubBlock;
    uint64_t mEndSignature;
};

class BlockPattern
{
public:
    BlockPattern() {}
    
    void fillBlock(uint64_t dir, uint64_t file, uint64_t block, uint64_t& offset)
    {
        for(uint64_t i = 0; i < MAXSUBBLOCKS; i++)
        {
            offset = offset + sizeof(SubBlockPattern);
            SubBlockPattern& subBlock = mSubBlocks[i];
            subBlock.fillSubBLock(dir, file, block, i, offset);
        }
    }

    int readVerifyBlock(uint64_t dir, uint64_t file, uint64_t block, uint64_t& offset)
    {
        for(uint64_t i = 0; i < MAXSUBBLOCKS; i++)
        {
            offset = offset + sizeof(SubBlockPattern);
            SubBlockPattern& subBlock = mSubBlocks[i];
            if (subBlock.readVerifySubBLock(dir, file, block, i, offset))
            {
                return -1;
            }
        }
        return 0;
    }

private:
    SubBlockPattern mSubBlocks[MAXSUBBLOCKS];
};

int fillFile(uint64_t dir, uint64_t file)
{
    int ret = 0;

    if (sizeof(BlockPattern) != (64 * 1024))
    {
        return -1;
    }

    char filename[64];

    sprintf(filename, "file%lu", file);

    int fd = open(filename, O_RDWR | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);

    if(fd < 0)
    {
        fd = open(filename, O_RDONLY);

        if (fd < 0)
        {
            std::cout << "File " << filename << " open failed fd " << fd << " error " << errno << std::endl;
            return -1;
        }
    }

    BlockPattern* block = new BlockPattern();
    uint64_t offset = 0;

    for (uint64_t i = 0; i < MAXBLOCKS; i++)
    {
        block->fillBlock(dir, file, i, offset);
        write(fd, (void *)block, sizeof(BlockPattern));
    }

    delete block;

    close(fd);

    return ret;
}

int readFile(uint64_t dir, uint64_t file)
{
    int ret = 0;

    if (sizeof(BlockPattern) != (64 * 1024))
    {
        return -1;
    }

    char filename[64];

    sprintf(filename, "file%lu", file);

    int fd = open(filename, O_RDONLY);

    if(fd < 0)
    {
        std::cout << "File " << filename << " open failed fd " << fd << " error " << errno << std::endl;
        return -1;
    }

    BlockPattern* block = new BlockPattern();
    uint64_t offset = 0;

    for (uint64_t i = 0; i < MAXBLOCKS; i++)
    {
        size_t readRet = read(fd, (void *)block, sizeof(BlockPattern));
        if (readRet != sizeof(BlockPattern))
        {
            std::cout << "Read failed" << std::endl;
            ret = -1;
            break;
        }
        if (block->readVerifyBlock(dir, file, i, offset))
        {
            ret = -1;
            break;
        }
    }

    delete block;

    close(fd);

    return ret;    
}

int fillDir()
{
    return 0;
}

int main(int argc, char* argv[])
{
    if (sizeof(SubBlockPattern) != 64)
    {
        return -1;
    }

    int write = 1;

    if (argc != 2)
    {
        std::cout << "Arguments wrong or not provided. Usage: " << argv[0] << " 0 (write) OR 1(read)" <<  std::endl;
        return -1;
    }

    int read = atoi(argv[1]);

    if (read)
    {
        if (readFile(1, 1))
        {
            std::cout << "Read file failed" << std::endl;
            return -1;
        }
        std::cout << "Read and verify from file file1 done" << std::endl;
    }
    else
    {
        if (fillFile(1, 1))
        {
            std::cout << "Fill file failed" << std::endl;
            return -1;
        }
        std::cout << "Writing to file file1 done" << std::endl;
    }

    return 0;
}
