package testing;

import static org.junit.jupiter.api.Assertions.*;

import org.junit.jupiter.api.Test;

class testlist {

	@Test
	void test() {
		Library lib=new Library();
		//Book book = new Book("chemistry", 5,lib);
		lib.addBook("chemistry", 5);
		lib.addBook("math", 5);
		lib.addBook("english", 5);
		assertEquals(3, lib.get_book_list().length);

	}

}
