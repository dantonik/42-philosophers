FROM alpine:3.12

# Install the necessary packages for building and testing C programs
RUN apk add --no-cache gcc libc-dev make valgrind

# Set the working directory to the directory containing your source files
WORKDIR /src

# Copy the source files into the container
COPY . .

# Compile the C program
RUN make re

# Run the C program with valgrind
CMD ["valgrind --tool=helgrind", "./philo 5 800 200 200"]