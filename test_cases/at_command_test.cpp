#include <stdio.h>
#include <stdint.h>
#include <string.h>

#include "gtest/gtest.h"
#include "core/common/inc/ring_buffer.h"
#include "utils/at_command/inc/at_command.h"

#define MAX_BUFFER_LENGTH (25U)

void CallbackOfATCommand(unsigned int argc, const char *argv[]);

class ATCommandTest: public testing::Test
{
public:
    static unsigned int s_argc;
    static const char *s_argv[MAX_NUMBER_OF_AT_COMMAND_PARAMETERS];

protected:
    ATCommand m_command;
    RingBuffer m_ringBuffer;
    uint8_t m_buffer[MAX_BUFFER_LENGTH + 1];

    virtual void SetUp()
    {
        ConstructATCommand(&m_command, "+TEST", CallbackOfATCommand);

        memset(m_buffer, 0, MAX_BUFFER_LENGTH + 1);
        ConstructRingBuffer(&m_ringBuffer, m_buffer, MAX_BUFFER_LENGTH);
        SetCallbackToRingBuffer(&m_ringBuffer, RingBufferCallbackOfATCommand);
    }

    virtual void TearDown()
    {
        DestructATCommand(&m_command);
        DestructRingBuffer(&m_ringBuffer);
    }

    void RunTest(unsigned int argc, const char *argv[]);
    void RunTestWithBuffer(unsigned int argc, const char *argv[]);
    int BuildCommand(char *buffer, unsigned int argc, const char *argv[]);
};

TEST_F(ATCommandTest, ProcessWithoutParameter)
{
    unsigned int argc = 1;
    const char *argv[] = {"AT+TEST"};

    // AT+TEST\r
    this->RunTest(argc, argv);
}

TEST_F(ATCommandTest, ProcessWithParameter)
{
    unsigned int argc = 4;
    const char *argv[] = {"AT+TEST", "1", "2", "3"};

    // AT+TEST=1,2,3\r
    this->RunTest(argc, argv);
}

TEST_F(ATCommandTest, ProcessBufferWithoutParameter)
{
    unsigned int argc = 1;
    const char *argv[] = {"AT+TEST"};

    // AT+TEST\r
    this->RunTestWithBuffer(argc, argv);
}

TEST_F(ATCommandTest, ProcessBufferWithParameter)
{
    unsigned int argc = 4;
    const char *argv[] = {"AT+TEST", "1", "2", "3"};

    // AT+TEST=1,2,3\r
    this->RunTestWithBuffer(argc, argv);
}

TEST_F(ATCommandTest, ProcessNotExist)
{
    unsigned int argc = 1;
    const char *argv[] = {"AT+HELLO"};

    // AT+HELLO\r
    this->RunTest(argc, argv);
}

unsigned int ATCommandTest::s_argc = 0;
const char *ATCommandTest::s_argv[MAX_NUMBER_OF_AT_COMMAND_PARAMETERS] = {NULL};

void ATCommandTest::RunTest(unsigned int argc, const char *argv[])
{
    char buffer[MAX_BUFFER_LENGTH + 1] = {0};
    ASSERT_NE(0, this->BuildCommand(buffer, argc, argv));

    ATCommandTest::s_argc = argc;
    memcpy(ATCommandTest::s_argv, argv, argc * sizeof(const char *));
    ProcessATCommand(buffer);
}

void ATCommandTest::RunTestWithBuffer(unsigned int argc, const char *argv[])
{
    char buffer[MAX_BUFFER_LENGTH + 1] = {0};
    int length = this->BuildCommand(buffer, argc, argv);

    ASSERT_NE(0, length);

    ATCommandTest::s_argc = argc;
    memcpy(ATCommandTest::s_argv, argv, argc * sizeof(const char *));
    ASSERT_TRUE(WriteRingBuffer(&m_ringBuffer, (uint8_t *)buffer, length));
}

int ATCommandTest::BuildCommand(
    char *buffer,
    unsigned int argc,
    const char *argv[])
{
    int length = 0;

    for (unsigned int i = 0; i < argc; i++)
    {
        strcpy(buffer + length, argv[i]);
        length += strlen(argv[i]);

        if (i == 0 && argc != 1)
        {
            buffer[length++] = '=';
        }
        else if (i != argc - 1)
        {
            buffer[length++] = ',';
        }
        else
        {
            buffer[length++] = '\r';
        }
    }

    printf("[ DEBUG    ] %s\r\n", buffer);
    return length;
}

void CallbackOfATCommand(unsigned int argc, const char *argv[])
{
    EXPECT_EQ(ATCommandTest::s_argc, argc);

    for (unsigned int i = 0; i < argc; i++)
    {
        EXPECT_STREQ(ATCommandTest::s_argv[i], argv[i]);
        printf("[ DEBUG    ] argv[%d]: %s\r\n", i, argv[i]);
    }
}

