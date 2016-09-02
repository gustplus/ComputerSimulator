#include <stdio.h>
#include <assert.h>
#include "gates.h"

static void test_notgate() {
	printf("test not gate\n");
	gate::NotGate not_gate;
	gate::ManualInput input;
	gate::LogOutput output;
	not_gate.addInput(&input);
	not_gate.setOutput(&output);

	input.input((gate::volt)0);
	gate::volt ret = not_gate.check();
	assert(ret == (gate::volt)1);

	input.input((gate::volt)1);
	ret = not_gate.check();
	assert(ret == (gate::volt)0);
	printf("test not gate finished\n");
}

static void test_andgate() {
	printf("test and gate\n");
	gate::AndGate and_gate;
	gate::ManualInput input0;
	and_gate.addInput(&input0);
	gate::ManualInput input1;
	and_gate.addInput(&input1);
	gate::LogOutput output;
	and_gate.setOutput(&output);

	input0.input((gate::volt)0);
	input1.input((gate::volt)0);
	gate::volt ret = and_gate.check();
	assert(ret == (gate::volt)0);

	input0.input((gate::volt)0);
	input1.input((gate::volt)1);
	ret = and_gate.check();
	assert(ret == (gate::volt)0);

	input0.input((gate::volt)1);
	input1.input((gate::volt)0);
	ret = and_gate.check();
	assert(ret == (gate::volt)0);

	input0.input((gate::volt)1);
	input1.input((gate::volt)1);
	ret = and_gate.check();
	assert(ret == (gate::volt)1);
	printf("test and gate finished\n");
}

static void test_nandgate() {
	printf("test nand gate\n");
	gate::NAndGate nand_gate;
	gate::ManualInput input0;
	nand_gate.addInput(&input0);
	gate::ManualInput input1;
	nand_gate.addInput(&input1);
	gate::LogOutput output;
	nand_gate.setOutput(&output);

	input0.input((gate::volt)0);
	input1.input((gate::volt)0);
	printf("0\n");
	gate::volt ret = nand_gate.check();
	printf("1\n");
	assert(ret == (gate::volt)1);

	input0.input((gate::volt)0);
	input1.input((gate::volt)1);
	ret = nand_gate.check();
	assert(ret == (gate::volt)1);

	input0.input((gate::volt)1);
	input1.input((gate::volt)0);
	ret = nand_gate.check();
	assert(ret == (gate::volt)1);

	input0.input((gate::volt)1);
	input1.input((gate::volt)1);
	ret = nand_gate.check();
	assert(ret == (gate::volt)0);
	printf("test nand gate finished\n");

}

static void test_norgate() {
	printf("test or gate\n");
	gate::NOrGate or_gate;
	gate::ManualInput input0;
	or_gate.addInput(&input0);
	gate::ManualInput input1;
	or_gate.addInput(&input1);
	gate::LogOutput output;
	or_gate.setOutput(&output);

	input0.input((gate::volt)0);
	input1.input((gate::volt)0);
	gate::volt ret = or_gate.check();
	assert(ret == (gate::volt)1);

	input0.input((gate::volt)0);
	input1.input((gate::volt)1);
	ret = or_gate.check();
	assert(ret == (gate::volt)0);

	input0.input((gate::volt)1);
	input1.input((gate::volt)0);
	ret = or_gate.check();
	assert(ret == (gate::volt)0);

	input0.input((gate::volt)1);
	input1.input((gate::volt)1);
	ret = or_gate.check();
	assert(ret == (gate::volt)0);
	printf("test or gate finished\n");
}

static void test_orgate() {
	printf("test or gate\n");
	gate::OrGate or_gate;
	gate::ManualInput input0;
	or_gate.addInput(&input0);
	gate::ManualInput input1;
	or_gate.addInput(&input1);
	gate::LogOutput output;
	or_gate.setOutput(&output);

	input0.input((gate::volt)0);
	input1.input((gate::volt)0);
	gate::volt ret = or_gate.check();
	assert(ret == (gate::volt)0);

	input0.input((gate::volt)0);
	input1.input((gate::volt)1);
	ret = or_gate.check();
	assert(ret == (gate::volt)1);

	input0.input((gate::volt)1);
	input1.input((gate::volt)0);
	ret = or_gate.check();
	assert(ret == (gate::volt)1);

	input0.input((gate::volt)1);
	input1.input((gate::volt)1);
	ret = or_gate.check();
	assert(ret == (gate::volt)1);
	printf("test or gate finished\n");
}

int main(int argc, const char **argv) {
	test_notgate();
	test_andgate();
	test_nandgate();
	test_orgate();
	test_norgate();
	printf("all test passed\n");
	return 0;
}
