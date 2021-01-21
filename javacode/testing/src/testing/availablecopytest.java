package testing;

import static org.junit.jupiter.api.Assertions.*;

import org.junit.jupiter.api.Test;

class availablecopytest {

	@Test
	void test() {
		Library lib=new Library();
		Book book=new Book("physics",10,lib);
		assertEquals(10, book.available_books());
	}

}
