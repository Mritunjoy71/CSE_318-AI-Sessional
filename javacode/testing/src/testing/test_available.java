package testing;

import static org.junit.jupiter.api.Assertions.*;

import org.junit.jupiter.api.Test;

class test_available {

	@Test
	void test() {
		Library lib=new Library();
		Book book = new Book("chemistry", 5,lib);
		lib.addBook("chemistry", 5);
		assertEquals(true, lib.isAvailable(book));
	}

}
