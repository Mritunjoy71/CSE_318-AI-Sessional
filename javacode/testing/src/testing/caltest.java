package testing;

import static org.junit.jupiter.api.Assertions.*;

import org.junit.jupiter.api.Test;

class caltest {

	@Test
	void test() {
		Calculator cal=new Calculator();
		assertEquals(10.0, cal.add(5.0, 5.0));
	}

}
